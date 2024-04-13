//
// Created by romka on 13.12.2023.
//
#include "../include/cpu_service.h"

namespace cpu {

    CpuService::CpuService(std::string name): nameOfCpu(std::move(name)) {}

    CpuService &CpuService::fill_cpu(const std::deque <DequeType> &deque) {
        //std::cout << "I am in fill_cpu cpuService\n";
        for (const auto& element: deque) {
            if (element.second.first) {
                cpu.get_data_memory().add_operand(element.first[0], Operand(element.first[1]));
                continue;
            }
            if (element.second.second) {
                cpu.get_program_memory().add_instruction(std::make_unique<Operator>
                        (element.first[0], element.first[1], element.first[2]));
                continue;
            }
            if (element.first.size() == 3) {
                cpu.get_program_memory().add_instruction(std::make_unique<UnaryCommand>
                        (element.first[0], element.first[1], element.first[2]));
                continue;
            }
            cpu.get_program_memory().add_instruction(std::make_unique<BinaryCommand>
                    (element.first[0], element.first[1], element.first[2], element.first[3]));
        }
        return *this;
    }

    std::size_t CpuService::get_variable_type(const Variable &value) {
        if (value.get_type() == TypeOfVariable::REGISTER)
            return cpu.get_register(value.get_index()).get_value().index();
        return cpu.get_data_memory().get_operand(value.get_name()).get_value().index();
    }

    std::size_t CpuService::identify_unit(const std::string &instructionName) {
        if (instructionName == "LSHIFT" || instructionName == "RSHIFT")
            return 2;
        return 1;
    }

    std::size_t CpuService::identify_unit(const UnaryCommand *command) {
        if (get_variable_type(command->get_value()) == 1)// double
            return 0;
        return identify_unit(command->get_name());
    }

    std::size_t CpuService::identify_unit(const BinaryCommand *command) {
        auto [first, second] = command->get_variables();
        if (get_variable_type(first) == 1 || get_variable_type(second) == 1)
            return 0;
        return identify_unit(command->get_name());
    }

    std::size_t CpuService::find_instruction(const std::string &flagName, std::size_t idx) {
        for (std::size_t i = idx; i < cpu.get_program_memory().get_number(); ++i)
            if (cpu.get_program_memory().get_instruction(i)->get_identifier() == flagName)
                return i;
        throw std::logic_error("FindIdentifierError");
    }

    std::pair<std::size_t, TypeOfInstruction> CpuService::process_operator(const Operator *ptr, std::size_t idx) {
        if (ptr->get_name() == "GOTO") {
            return std::make_pair(find_instruction(ptr->get_flag(), idx), TypeOfInstruction::GOTO);
        }
        if (ptr->get_name() == "THREAD") {
            return std::make_pair(find_instruction(ptr->get_flag(), idx), TypeOfInstruction::THREAD);
        }
        return std::make_pair(Core::nPos, TypeOfInstruction::THREAD_DONE);
    }

    void CpuService::process_command(const UnaryCommand *ptr, std::size_t threadNumber) {
        cpu.lock_core(threadNumber);
        cpu.get_core(threadNumber).get_unit(identify_unit(ptr))->process_instruction(
                ptr, cpu.get_data_memory(), cpu.get_registers());
        cpu.unlock_core(threadNumber);
    }

    void CpuService::process_command(const BinaryCommand *ptr, std::size_t threadNumber) {
        cpu.lock_core(threadNumber);
        //std::cout << "\t\tunit: " << identify_unit(ptr) << "\n";
        cpu.get_core(threadNumber).get_unit(identify_unit(ptr))->process_instruction(
                ptr, cpu.get_data_memory(), cpu.get_registers());
        cpu.unlock_core(threadNumber);
    }

    std::pair<std::size_t, TypeOfInstruction> CpuService::process_instruction(
            const std::unique_ptr<Instruction>& ptr, std::size_t idx, std::size_t threadNumber) {
        //std::cout << "in process_instruction cpuService\n";
        if (auto operatorPtr = dynamic_cast<const Operator*>(ptr.get()); operatorPtr != nullptr) {
            //std::cout << "\toperator\n";
            return process_operator(operatorPtr, idx);
        }
        if (auto unaryPtr = dynamic_cast<const UnaryCommand*>(ptr.get()); unaryPtr != nullptr) {
            //std::cout << "\tunaryOperator\n";
            process_command(unaryPtr, threadNumber);
        } else {
            //std::cout << "\tbinaryOperator\n";
            auto binaryPtr = dynamic_cast<const BinaryCommand*>(ptr.get());
            process_command(binaryPtr, threadNumber);
        }
        return std::make_pair<>(cpu.get_program_memory().get_number(), TypeOfInstruction::COMMAND);
    }

    CPU &CpuService::get_cpu() {
        return cpu;
    }

    const std::string &CpuService::get_name() const {
        return nameOfCpu;
    }
}
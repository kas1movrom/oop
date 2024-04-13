//
// Created by romka on 13.12.2023.
//

#ifndef CPU_FINAL_CPU_SERVICE_H
#define CPU_FINAL_CPU_SERVICE_H

#include "../../../cpu/include/cpu.h"

#include <deque>
#include <thread>

namespace cpu {

    enum TypeOfInstruction {
        COMMAND,
        GOTO,
        THREAD,
        THREAD_DONE
    };

    class CpuService {

    private:

        std::string nameOfCpu;
        CPU& cpu = CPU::build_cpu(nameOfCpu);

    public:

        using DequeType = std::pair<std::vector<std::string>, std::pair<bool, bool>>;

        explicit CpuService(std::string name);

        CpuService& fill_cpu(const std::deque<DequeType>& deque);

        std::size_t get_variable_type(const Variable& value);

        std::size_t identify_unit(const UnaryCommand* command);
        std::size_t identify_unit(const BinaryCommand* command);
        std::size_t identify_unit(const std::string& instructionName);

        std::pair<std::size_t, TypeOfInstruction> process_instruction(
                const std::unique_ptr<Instruction>& ptr, std::size_t idx, std::size_t threadNumber);

        std::pair<std::size_t, TypeOfInstruction> process_operator(const Operator* ptr, std::size_t idx);
        void process_command(const UnaryCommand* ptr, std::size_t threadNumber);
        void process_command(const BinaryCommand* ptr, std::size_t threadNumber);

        std::size_t find_instruction(const std::string& flagName, std::size_t idx);

        CPU& get_cpu();

        [[nodiscard]] const std::string& get_name() const;
    };

}

#endif //CPU_FINAL_CPU_SERVICE_H

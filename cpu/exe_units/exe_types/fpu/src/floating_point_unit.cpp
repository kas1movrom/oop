//
// Created by romka on 13.12.2023.
//
#include "../include/floating_point_unit.h"

namespace cpu {

    std::string FloatingPointUnit::get_unit() const {
        return "FloatingPointUnit";
    }

    void FloatingPointUnit::process_instruction(const UnaryCommand *command, DataMemory &memory,
                                                kas::vector<std::pair<Operand, std::mutex>> &registers) {
        //std::cout << "process_instruction fpU\n";
        Operand& operand = get_operand(command->get_value(), memory, registers);
        calculated_double(operand, Operand(0.0), "MINUS");
        unlock(command->get_value(), memory, registers);
    }

    void FloatingPointUnit::process_instruction(const BinaryCommand *command, DataMemory &memory,
                                                kas::vector<std::pair<Operand, std::mutex>> &registers) {
        //std::cout << "process_instruction fpU\n";
        auto [first, second] = command->get_variables();
        Operand& firstOperand = get_operand(first, memory, registers);
        const Operand& secondOperand = get_operand(second, memory, registers);
        //std::cout << "go to calculated...\n";
        calculated_double(firstOperand, secondOperand, command->get_name());
        unlock(first, memory, registers);
        unlock(second, memory, registers);
    }
}
//
// Created by romka on 13.12.2023.
//
#include "../include/arithmetic_logic_unit.h"

namespace cpu {

    std::string ArithmeticLogicUnit::get_unit() const {
        return "ArithmeticLogicUnit";
    }

    void ArithmeticLogicUnit::process_instruction(const UnaryCommand *command, DataMemory &memory,
                                                  kas::vector<std::pair<Operand, std::mutex>> &registers) {
        //std::cout << "process_instruction ALU\n";
        Operand& operand = get_operand(command->get_value(), memory, registers);
        calculated_long(operand, Operand(), command->get_name());
        unlock(command->get_value(), memory, registers);
    }

    void ArithmeticLogicUnit::process_instruction(const BinaryCommand *command, DataMemory &memory,
                                                  kas::vector<std::pair<Operand, std::mutex>> &registers) {
        //std::cout << "process_instruction ALU\n";
        auto [first, second] = command->get_variables();
        Operand& firstOperand = get_operand(first, memory, registers);
        const Operand& secondOperand = get_operand(second, memory, registers);
        calculated_long(firstOperand, secondOperand, command->get_name());
        unlock(first, memory, registers);
        unlock(second, memory, registers);
    }
}
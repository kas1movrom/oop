//
// Created by romka on 13.12.2023.
//
#include "../include/base_shifter.h"

namespace cpu {

    std::string BaseShifter::get_unit() const {
        return "BaseShifter";
    }

    void BaseShifter::process_instruction(const UnaryCommand *command, DataMemory &memory,
                                          kas::vector<std::pair<Operand, std::mutex>> &registers) {
        throw std::invalid_argument("BaesShifterInvalidArgument");
    }

    void BaseShifter::process_instruction(const BinaryCommand *command, DataMemory &memory,
                                          kas::vector<std::pair<Operand, std::mutex>> &registers) {
        //std::cout << "process_instruction bs\n";
        auto [first, second] = command->get_variables();
        Operand& firstOperand = get_operand(first, memory, registers);
        const Operand& secondOperand = get_operand(second, memory, registers);
        calculated_long(firstOperand, secondOperand, command->get_name());
        unlock(first, memory, registers);
        unlock(second, memory, registers);
    }
}
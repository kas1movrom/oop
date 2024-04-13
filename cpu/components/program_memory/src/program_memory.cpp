//
// Created by romka on 12.12.2023.
//
#include "../include/program_memory.h"

namespace cpu {


    std::size_t ProgramMemory::get_number() const {
        return instructions.size();
    }

    const std::unique_ptr<Instruction> &ProgramMemory::get_instruction(std::size_t idx) const {
        return instructions.at(idx);
    }

    ProgramMemory &ProgramMemory::add_instruction(std::unique_ptr<Instruction> &&instruction) {
        instructions.push_back(std::move(instruction));
        return *this;
    }
}
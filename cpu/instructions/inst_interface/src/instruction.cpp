//
// Created by romka on 12.12.2023.
//
#include "../include/instruction.h"

namespace cpu {

    Instruction::Instruction(std::string name, std::string identifier):
                            name(std::move(name)), identifier(std::move(identifier)) {}

    const std::string &Instruction::get_name() const {
        return name;
    }

    const std::string &Instruction::get_identifier() const {
        return identifier;
    }

}
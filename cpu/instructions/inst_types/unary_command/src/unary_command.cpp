//
// Created by romka on 12.12.2023.
//
#include "../include/unary_command.h"

namespace cpu {

    UnaryCommand::UnaryCommand(Variable value, const std::string &name, const std::string &identifier):
            Instruction(name, identifier), value(std::move(value)) {}

    UnaryCommand::UnaryCommand(const std::string &variableName, const std::string &name,
                               const std::string &identifier):
            Instruction(name, identifier), value(variableName) {}

    std::string UnaryCommand::get_instruction() const {
        std::string result = get_identifier() + ": " + get_name() + " " + value.get_name() + "\n";
        return result;
    }

    const Variable &UnaryCommand::get_value() const {
        return value;
    }

    Instruction *UnaryCommand::clone() {
        return new UnaryCommand(*this);
    }

}
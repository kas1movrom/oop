//
// Created by romka on 12.12.2023.
//
#include "../include/binary_command.h"

namespace cpu {

    BinaryCommand::BinaryCommand(Variable value1, Variable value2, const std::string &name,
                                 const std::string &identifier):
            Instruction(name, identifier), values(std::move(value1), std::move(value2)) {}

    BinaryCommand::BinaryCommand(const std::string& value1, const std::string &value2, const std::string &name,
                                 const std::string &identifier):
            Instruction(name, identifier), values(value1, value2) {}

    std::string BinaryCommand::get_instruction() const {
        std::string result = get_identifier() + ": " + get_name() + " " + values.first.get_name() +
                             " " + values.second.get_name() + "\n";
        return result;
    }

    BinaryCommand::ConstPairVariables BinaryCommand::get_variables() const {
        return values;
    }

    Instruction *BinaryCommand::clone() {
        return new BinaryCommand(*this);
    }
}
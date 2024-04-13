//
// Created by romka on 12.12.2023.
//
#include "../include/operator.h"

namespace cpu {

    Operator::Operator(std::string flag, const std::string &name, const std::string &identifier):
            Instruction(name, identifier), flag(std::move(flag)) {}

    const std::string &Operator::get_flag() const {
        return flag;
    }

    std::string Operator::get_instruction() const {
        std::string result =  get_identifier() + ": " + get_name() + " " + flag + "\n";
        return result;
    }

    Instruction *Operator::clone() {
        return new Operator(*this);
    }
}
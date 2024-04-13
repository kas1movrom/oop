//
// Created by romka on 12.12.2023.
//
#include "../include/variable.h"

namespace cpu {

    Variable::Variable(std::string name): name(std::move(name)) {
        if (this->name[0] == '_') {
            type = TypeOfVariable::REGISTER;
        } else {
            type = TypeOfVariable::IDENTIFIER;
        }
    }

    TypeOfVariable Variable::get_type() const {
        return type;
    }

    const std::string &Variable::get_name() const {
        return name;
    }

    std::size_t Variable::get_index() const {
        return std::stoull(name.substr(1));
    }

}
//
// Created by romka on 12.12.2023.
//
#include "../include/operand.h"

namespace cpu {

    Operand::Operand(long long value): value(value) {}

    Operand::Operand(double value): value(value) {}

    Operand::Operand(): Operand(0ll) {}

    Operand::Operand(const std::string &str) {
        bool findPoint = str.find('.') != std::string::npos;
        if (findPoint) {
            value = std::stod(str);
        } else {
            value = std::stoll(str);
        }
    }

    Operand::variant_t Operand::get_value() const {
        return value;
    }

    Operand &Operand::set_value(double val) {
        value = val;
        return *this;
    }

    Operand &Operand::set_value(long long val) {
        value = val;
        return *this;
    }

    std::string Operand::get_operand() const {
        std::string result = (value.index() == 0 ?
                std::to_string(std::get<long long>(value)) + " -- LONG\n" :
                std::to_string(std::get<double>(value)) + " -- DOUBLE\n");
        return result;
    }
}
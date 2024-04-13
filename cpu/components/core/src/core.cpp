//
// Created by romka on 13.12.2023.
//
#include "../include/core.h"

namespace cpu {

    Core::Core() {
        units[0] = std::make_unique<FloatingPointUnit>(300);
        units[1] = std::make_unique<ArithmeticLogicUnit>(150);
        units[2] = std::make_unique<BaseShifter>(100);
    }

    std::size_t Core::get_current_inst() const {
        return curInstruction;
    }

    Core &Core::set_current_inst(std::size_t instructions) {
        curInstruction = instructions;
        return *this;
    }

    std::unique_ptr<ExeUnit> &Core::get_unit(std::size_t index) {
        return units[index];
    }
}
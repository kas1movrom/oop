//
// Created by romka on 13.12.2023.
//
#include "../include/cpu.h"

namespace cpu {
    CPU::CPU(std::string name): name(std::move(name)), blockRegisters(numberRegisters), programMemory(),
                                dataMemory(DataMemory::numbersOperand) {}

    CPU &CPU::build_cpu(const std::string& nameOfCpu) {
        static CPU cpu(nameOfCpu);
        return cpu;
    }

    const std::string &CPU::get_name() const {
        return name;
    }

    DataMemory &CPU::get_data_memory() {
        return dataMemory;
    }

    ProgramMemory &CPU::get_program_memory() {
        return programMemory;
    }

    const ProgramMemory &CPU::get_program_memory() const {
        return programMemory;
    }

    Core &CPU::get_core(std::size_t idx) {
        return cores[idx].first;
    }

    Operand &CPU::get_register(std::size_t idx) {
        return blockRegisters[idx].first;
    }

    CPU &CPU::lock_core(std::size_t idx) {
        cores[idx].second.lock();
        return *this;
    }

    CPU &CPU::unlock_core(std::size_t idx) {
        cores[idx].second.unlock();
        return *this;
    }

    kas::vector<std::pair<Operand, std::mutex>> &CPU::get_registers() {
        return blockRegisters;
    }
}
//
// Created by romka on 12.12.2023.
//

#ifndef CPU_FINAL_PROGRAM_MEMORY_H
#define CPU_FINAL_PROGRAM_MEMORY_H

#include "../../../instructions/inst_interface/include/instruction.h"

#include <vector>
#include <memory>

namespace cpu {

    class ProgramMemory {

    private:

        std::vector<std::unique_ptr<Instruction>> instructions;

    public:

        ProgramMemory() = default;

        ProgramMemory &add_instruction(std::unique_ptr<Instruction> &&instruction);

        [[nodiscard]] std::size_t get_number() const;

        [[nodiscard]] const std::unique_ptr<Instruction> &get_instruction(std::size_t idx) const;

    };
}

#endif //CPU_FINAL_PROGRAM_MEMORY_H

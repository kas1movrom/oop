//
// Created by romka on 13.12.2023.
//

#ifndef CPU_FINAL_BASE_SHIFTER_H
#define CPU_FINAL_BASE_SHIFTER_H

#include "../../../exe_interface/include/exe_unit.h"

namespace cpu {

    class BaseShifter:
            public ExeUnit {

    public:

        using ExeUnit::ExeUnit;

        [[nodiscard]] std::string get_unit() const final;

        void process_instruction(const BinaryCommand *command, DataMemory &memory,
                                 kas::vector<std::pair<Operand, std::mutex>> &registers) final;
        void process_instruction(const UnaryCommand *command, DataMemory &memory,
                                 kas::vector<std::pair<Operand, std::mutex>> &registers) final;

        ~BaseShifter() override = default;

    };

}


#endif //CPU_FINAL_BASE_SHIFTER_H

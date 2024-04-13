//
// Created by romka on 12.12.2023.
//

#ifndef CPU_FINAL_OPERATOR_H
#define CPU_FINAL_OPERATOR_H

#include "../../../inst_interface/include/instruction.h"

namespace cpu {

    class Operator:
            public Instruction {

    private:

        std::string flag;

    public:

        explicit Operator(std::string flag, const std::string& name, const std::string& identifier = "");

        [[nodiscard]] const std::string& get_flag() const;

        [[nodiscard]] std::string get_instruction() const final;

        Instruction* clone() final;

        ~Operator() override = default;

    };

}

#endif //CPU_FINAL_OPERATOR_H

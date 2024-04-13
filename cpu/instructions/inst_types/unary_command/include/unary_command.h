//
// Created by romka on 12.12.2023.
//

#ifndef CPU_FINAL_UNARY_COMMAND_H
#define CPU_FINAL_UNARY_COMMAND_H

#include "../../../inst_interface/include/instruction.h"

namespace cpu {

    class UnaryCommand:
            public Instruction {

    private:

        Variable value;

    public:

        UnaryCommand(Variable value, const std::string& name, const std::string& identifier = "");
        UnaryCommand(const std::string& variableName, const std::string& name, const std::string& identifier = "");

        [[nodiscard]] const Variable& get_value() const;

        [[nodiscard]] std::string get_instruction() const final;

        Instruction* clone() final;

        ~UnaryCommand() override = default;

    };

}

#endif //CPU_FINAL_UNARY_COMMAND_H

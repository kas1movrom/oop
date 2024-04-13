//
// Created by romka on 12.12.2023.
//

#ifndef CPU_FINAL_BINARY_COMMAND_H
#define CPU_FINAL_BINARY_COMMAND_H

#include "../../../inst_interface/include/instruction.h"

namespace cpu {

    class BinaryCommand:
            public Instruction {

    private:

        std::pair<Variable, Variable> values;

        using ConstPairVariables = const std::pair<Variable, Variable>&;

    public:

        BinaryCommand(Variable value1, Variable value2, const std::string& name, const std::string& identifier = "");
        BinaryCommand(const std::string& value1, const std::string& value2,
                      const std::string& name, const std::string& identifier = "");

        [[nodiscard]] ConstPairVariables get_variables() const;

        [[nodiscard]] std::string get_instruction() const final;

        Instruction* clone() final;

        ~BinaryCommand() override = default;

    };

}

#endif //CPU_FINAL_BINARY_COMMAND_H

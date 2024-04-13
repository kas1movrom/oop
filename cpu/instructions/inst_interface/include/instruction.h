//
// Created by romka on 12.12.2023.
//

#ifndef CPU_FINAL_INSTRUCTION_H
#define CPU_FINAL_INSTRUCTION_H

#include "../../../data_presentation/variable/include/variable.h"

namespace cpu {

    class Instruction {

    private:

        std::string name;
        std::string identifier;

    public:

        explicit Instruction(std::string name, std::string identifier = "");

        [[nodiscard]] const std::string& get_name() const;
        [[nodiscard]] const std::string& get_identifier() const;

        [[nodiscard]] virtual std::string get_instruction() const  = 0;
        virtual Instruction* clone() = 0;

        virtual ~Instruction() = default;

    };

}

#endif //CPU_FINAL_INSTRUCTION_H

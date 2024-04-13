//
// Created by romka on 12.12.2023.
//

#ifndef CPU_FINAL_VARIABLE_H
#define CPU_FINAL_VARIABLE_H

#include <iostream>
#include <string>

namespace cpu {

    enum TypeOfVariable {
        IDENTIFIER,
        REGISTER
    };

    class Variable {

    private:

        std::string name;
        TypeOfVariable type;

    public:

        explicit Variable(std::string name);

        [[nodiscard]] TypeOfVariable get_type() const;
        [[nodiscard]] const std::string& get_name() const;
        [[nodiscard]] std::size_t get_index() const;
    };

}

#endif //CPU_FINAL_VARIABLE_H

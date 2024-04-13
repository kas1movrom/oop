//
// Created by romka on 12.12.2023.
//

#ifndef CPU_FINAL_OPERAND_H
#define CPU_FINAL_OPERAND_H

#include <mutex>
#include <variant>
#include <string>

namespace cpu {

    class Operand {

    private:

        std::variant<long long, double> value;

        using variant_t = const std::variant<long long, double>&;

    public:

        Operand();
        explicit Operand(double value);
        explicit Operand(long long value);
        explicit Operand(const std::string& str);

        [[nodiscard]] variant_t get_value() const;

        Operand& set_value(long long val);
        Operand& set_value(double val);

        [[nodiscard]] std::string get_operand() const;


    };

}

#endif //CPU_FINAL_OPERAND_H

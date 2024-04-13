//
// Created by romka on 12.12.2023.
//

#ifndef CPU_FINAL_EXE_UNIT_H
#define CPU_FINAL_EXE_UNIT_H

#include "../../../instructions/inst_types/binary_command/include/binary_command.h"
#include "../../../instructions/inst_types/unary_command/include/unary_command.h"
#include "../../../components/data_memory/include/data_memory.h"

#include "../../../vector/include/myvector.h"

#include <thread>
#include <chrono>

using llong = long long;

namespace exeFunctions {
    inline llong mov(llong a, llong b) {
        return b;
    }
    inline llong mult(llong a, llong b) {
        return a * b;
    }
    inline llong divF(llong a, llong b) {
        return a / b;
    }
    inline llong add(llong a, llong b) {
        return a + b;
    }
    inline llong subs(llong a, llong b) {
        return a - b;
    }
    inline llong lshift(llong a, llong b) {
        return a << b;
    }
    inline llong rshift(llong a, llong b) {
        return a >> b;
    }
    inline llong orF(llong a, llong b) {
        return a | b;
    }
    inline llong andF(llong a, llong b) {
        return a & b;
    }
    inline llong xorF(llong a, llong b) {
        return a ^ b;
    }
    inline llong minus(llong a, llong b) {
        return -a;
    }
    inline llong notF(llong a, llong b) {
        return ~a;
    }

    inline double mov(double a, double b) {
        return b;
    }
    inline double mult(double a, double b) {
        return a * b;
    }
    inline double divF(double a, double b) {
        return a / b;
    }
    inline double add(double a, double b) {
        return a + b;
    }
    inline double subs(double a, double b) {
        return a - b;
    }
    inline double minus(double a, double b) {
        return -a;
    }
}

namespace cpu {
    using namespace exeFunctions;

    class ExeUnit {

    protected:

        bool busy;
        unsigned exeTime;

        inline static const std::unordered_map<std::string, llong(*)(llong, llong)> ll_functions =
        {
                {"MOV", mov},
                {"MULT", mult},
                {"DIV", divF},
                {"ADD", add},
                {"SUBS", subs},
                {"LSHIFT", lshift},
                {"RSHIFT", rshift},
                {"OR", orF},
                {"AND", andF},
                {"XOR", xorF},
                {"MINUS", minus},
                {"NOT", notF}
        };

        inline static const std::unordered_map<std::string, double(*)(double, double)> double_functions =
        {
                {"MOV", mov},
                {"MULT", mult},
                {"DIV", divF},
                {"ADD", add},
                {"SUBS", subs},
                {"MINUS", minus}
        };

        void calculated_long(Operand& first, const Operand& second, const std::string& name) const;
        void calculated_double(Operand& first, const Operand& second, const std::string& name) const;

        static double get_operand_value_double(const Operand& operand);
        static llong get_operand_value_long(const Operand& operand);

    public:

        explicit ExeUnit(unsigned time);

        static Operand& get_operand(const Variable& value, DataMemory& memory,
                                    kas::vector<std::pair<Operand, std::mutex>>& registers);

        static void lock(const Variable& variable, DataMemory& memory,
                  kas::vector<std::pair<Operand, std::mutex>>& registers);
        static void unlock(const Variable& variable, DataMemory& memory,
                    kas::vector<std::pair<Operand, std::mutex>>& registers);

        [[nodiscard]] bool is_busy() const;
        [[nodiscard]] unsigned get_exe_time() const;

        [[nodiscard]] virtual std::string get_unit() const = 0;

        virtual void process_instruction(const UnaryCommand* command, DataMemory& memory,
                                         kas::vector<std::pair<Operand, std::mutex>>& registers) = 0;
        virtual void process_instruction(const BinaryCommand* command, DataMemory& memory,
                                         kas::vector<std::pair<Operand, std::mutex>>& registers) = 0;

        virtual ~ExeUnit() = default;
    };
}


#endif //CPU_FINAL_EXE_UNIT_H

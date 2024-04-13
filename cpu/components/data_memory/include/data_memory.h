//
// Created by romka on 12.12.2023.
//

#ifndef CPU_FINAL_DATA_MEMORY_H
#define CPU_FINAL_DATA_MEMORY_H

#include <unordered_map>

#include "../../../data_presentation/operand/include/operand.h"

namespace cpu {

    class DataMemory {

    private:

        std::size_t capacity;
        std::unordered_map<std::string, std::pair<Operand, std::mutex>> data;

    public:

        static const std::size_t numbersOperand = 10;

        explicit DataMemory(std::size_t volume);

        DataMemory& add_operand(const std::string& identifier, const Operand& variable);

        [[nodiscard]] const Operand& get_operand(const std::string& identifier) const;
        Operand& get_operand(const std::string& identifier);

        [[nodiscard]] std::string get_data() const;

        DataMemory& lock(const std::string& identifier);
        DataMemory& unlock(const std::string& identifier);

        [[nodiscard]] std::size_t get_size() const;
    };

}

#endif //CPU_FINAL_DATA_MEMORY_H

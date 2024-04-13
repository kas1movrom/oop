//
// Created by romka on 12.12.2023.
//
#include "../include/data_memory.h"

namespace cpu {

    DataMemory::DataMemory(std::size_t volume) {
        if (volume <= 0)
            throw std::invalid_argument("DataMemoryInvalidArgument");
        capacity = volume;
        data.reserve(capacity);
    }

    DataMemory &DataMemory::add_operand(const std::string &identifier, const Operand &variable) {
        if (data.size() == capacity || data.find(identifier) != data.cend())
            throw std::invalid_argument("DataMemoryInvalidArgument");
        data[identifier].first = variable;
        return *this;
    }

    const Operand &DataMemory::get_operand(const std::string &identifier) const {
        return data.find(identifier)->second.first;
    }

    Operand &DataMemory::get_operand(const std::string &identifier) {
        return data[identifier].first;
    }

    std::string DataMemory::get_data() const {
        std::string result;
        for (const auto& iter: data)
            result += ("\t" + iter.first + ": " + iter.second.first.get_operand());
        return result;
    }

    DataMemory &DataMemory::lock(const std::string &identifier) {
        data[identifier].second.lock();
        return *this;
    }

    DataMemory &DataMemory::unlock(const std::string &identifier) {
        data[identifier].second.unlock();
        return *this;
    }

    std::size_t DataMemory::get_size() const {
        return data.size();
    }
}
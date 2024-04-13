//
// Created by romka on 12.12.2023.
//
#include "../include/exe_unit.h"

namespace cpu {

    ExeUnit::ExeUnit(unsigned int time): exeTime(time), busy(false) {}

    unsigned int ExeUnit::get_exe_time() const {
        return exeTime;
    }

    bool ExeUnit::is_busy() const {
        return busy;
    }

    Operand &ExeUnit::get_operand(const Variable &value, DataMemory &memory,
                                  kas::vector<std::pair<Operand, std::mutex>> &registers) {
        lock(value, memory, registers);
        if (value.get_type() == TypeOfVariable::REGISTER) {
            return registers[value.get_index()].first;
        }
        return memory.get_operand(value.get_name());
    }

    void ExeUnit::lock(const Variable &variable, DataMemory &memory,
                       kas::vector<std::pair<Operand, std::mutex>> &registers) {
        if (variable.get_type() == TypeOfVariable::REGISTER) {
            registers[variable.get_index()].second.lock();
            return;
        }
        memory.lock(variable.get_name());
    }

    void ExeUnit::unlock(const Variable &variable, DataMemory &memory,
                         kas::vector<std::pair<Operand, std::mutex>> &registers) {
        if (variable.get_type() == TypeOfVariable::REGISTER) {
            registers[variable.get_index()].second.unlock();
            return;
        }
        memory.unlock(variable.get_name());
    }

    void ExeUnit::calculated_long(Operand &first, const Operand &second, const std::string &name) const {
        //std::cout << "calculated long\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(exeTime));
        first.set_value(ll_functions.find(name)->second(get_operand_value_long(first),
                                                        get_operand_value_long(second)));
    }

    void ExeUnit::calculated_double(Operand &first, const Operand &second, const std::string &name) const {
        //std::cout << "calculated double\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(exeTime));
        first.set_value(double_functions.find(name)->second(get_operand_value_double(first),
                                                            get_operand_value_double(second)));
    }

    double ExeUnit::get_operand_value_double(const Operand &operand) {
        return (operand.get_value().index() == 0 ?
                static_cast<double>(std::get<llong>(operand.get_value())) : std::get<double>(operand.get_value()));
    }

    llong ExeUnit::get_operand_value_long(const Operand &operand) {
        return (operand.get_value().index() == 0 ?
                std::get<llong>(operand.get_value()) : static_cast<llong>(std::get<double>(operand.get_value())));
    }
}
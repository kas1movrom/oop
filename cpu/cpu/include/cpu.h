//
// Created by romka on 13.12.2023.
//

#ifndef CPU_FINAL_CPU_H
#define CPU_FINAL_CPU_H

#include "../../components/core/include/core.h"
#include "../../components/program_memory/include/program_memory.h"

#include "../../instructions/inst_types/binary_command/include/binary_command.h"
#include "../../instructions/inst_types/unary_command/include/unary_command.h"
#include "../../instructions/inst_types/operator/include/operator.h"


namespace cpu {

    class CPU {

    public:

        static const std::size_t numberRegisters = 16;
        static const std::size_t numberCores = 3;

    private:

        DataMemory dataMemory;
        ProgramMemory programMemory;

        std::string name;

        std::array<std::pair<Core, std::mutex>, numberCores> cores;
        kas::vector<std::pair<Operand, std::mutex>> blockRegisters;

        ~CPU() = default;

        explicit CPU(std::string name);


    public:

        CPU() = delete;
        CPU(const CPU&) = delete;
        CPU(CPU&&) = delete;
        CPU& operator=(const CPU&) = delete;
        CPU& operator=(CPU&&) = delete;

        static CPU& build_cpu(const std::string& nameOfCpu);

        [[nodiscard]] const std::string& get_name() const;

        DataMemory& get_data_memory();

        ProgramMemory& get_program_memory();
        [[nodiscard]] const ProgramMemory& get_program_memory() const;

        kas::vector<std::pair<Operand, std::mutex>>& get_registers();
        Core& get_core(std::size_t idx);
        Operand& get_register(std::size_t idx);

        CPU& lock_core(std::size_t idx);
        CPU& unlock_core(std::size_t idx);

    };

}


#endif //CPU_FINAL_CPU_H

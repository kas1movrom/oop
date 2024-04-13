//
// Created by romka on 14.12.2023.
//

#ifndef CPU_FINAL_MAIN_SERVICE_H
#define CPU_FINAL_MAIN_SERVICE_H

#include "../../parse_service/include/parse_service.h"
#include "../../cpu_service/include/cpu_service.h"

namespace cpu {

    class MainService {

    private:

        CpuService cpuService;

        std::vector<bool> breakPoints;

    public:

        explicit MainService(const std::string& name);

        MainService& fill_program(const std::string& filename);

        MainService& set_breakpoint(std::size_t idx);

        bool start_program();
        bool start_thread(std::size_t idx, std::size_t threadNumber);

        bool continue_work();
        bool continue_thread(std::size_t threadNumber);

        bool start_thread_func(std::thread& thread, std::size_t idx, std::size_t threadNumber);
        bool continue_thread_func(std::thread& thread, std::size_t idx);

        bool start_thread_func(std::thread& thread1, std::thread& thread2, std::size_t idx, std::size_t threadNumber);

        std::string show_program_memory();
        std::string show_data_memory();
        std::string show_registres();

        [[nodiscard]] const std::string& get_name() const;

        std::size_t get_size_data();

        [[nodiscard]] const std::vector<bool>& get_breakpoints() const;
    };

}

#endif //CPU_FINAL_MAIN_SERVICE_H

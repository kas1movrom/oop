//
// Created by romka on 14.12.2023.
//
#include "../include/main_service.h"

namespace cpu {

    MainService::MainService(const std::string &name): cpuService(name) {}

    MainService &MainService::fill_program(const std::string &filename) {
        std::ifstream inStream(filename);
        if (!inStream.is_open()) {
            throw std::invalid_argument("CannotFindFile");
        }
        cpuService.fill_cpu(ParseService::parse_file(inStream));
        breakPoints.resize(cpuService.get_cpu().get_program_memory().get_number(), false);
        return *this;
    }

    MainService &MainService::set_breakpoint(std::size_t idx) {
        breakPoints[idx] = true;
        return *this;
    }

    bool MainService::start_thread_func(std::thread &thread, std::size_t idx, std::size_t threadNumber) {
        bool resultThread;
        thread = std::thread([&]() {
            resultThread = start_thread(idx, threadNumber);
        });
        thread.detach();
        return resultThread;
    }

    bool MainService::continue_thread_func(std::thread &thread, std::size_t idx) {
        bool resultThread;
        thread = std::thread([&]() {
            resultThread = continue_thread(idx);
        });
        thread.detach();
        return resultThread;
    }

    bool MainService::start_thread_func(std::thread &thread1, std::thread &thread2, std::size_t idx,
                                        std::size_t threadNumber) {
        return (threadNumber == 1 ?
            start_thread_func(thread1, idx, threadNumber) : start_thread_func(thread2, idx, threadNumber));
    }

    bool MainService::start_thread(std::size_t idx, std::size_t threadNumber) {
        //std::cout << "in start thread\n";
        CPU& cpu = cpuService.get_cpu();
        for (std::size_t i = idx; i < cpu.get_program_memory().get_number(); ++i) {
//            std::cout << "indexInThread: " << i << cpu.get_program_memory().get_instruction(i)->get_instruction();
            cpu.get_core(threadNumber).set_current_inst(i);
            if (breakPoints[i]) {
//                std::cout << "in breakpoint\n";
                return true;
            }
            auto result = cpuService.process_instruction(cpu.get_program_memory().get_instruction(i), i, threadNumber);
            if (result.second == TypeOfInstruction::COMMAND) {
                continue;
            }
            if (result.second == TypeOfInstruction::GOTO) {
                i = result.first - 1;
                continue;
            }
            if (result.second == TypeOfInstruction::THREAD_DONE) {
                cpu.get_core(threadNumber).set_current_inst(-1);
                return false;
            }
        }
        return false;
    }

    bool MainService::start_program() {
        std::thread thread1, thread2;
        std::array<bool, 3> workedThreadsArray = {true, false, false};
        CPU& cpu = cpuService.get_cpu();
        for (std::size_t i = 0; i < cpu.get_program_memory().get_number(); ++i) {
            cpu.get_core(0).set_current_inst(i);
            if (breakPoints[i]) {
                return true;
            }
            auto result = cpuService.process_instruction(cpu.get_program_memory().get_instruction(i), i, 0);
            if (result.second == TypeOfInstruction::COMMAND)
                continue;
            if (result.second == TypeOfInstruction::GOTO) {
                i = result.first - 1;
                continue;
            }
            if (result.second == TypeOfInstruction::THREAD) {
                std::size_t j;
                for (j = 1; j <= 2; ++j) {
                    if (!workedThreadsArray[j]) {
                        workedThreadsArray[j] = true;
                        break;
                    }
                }
                if (j == 1) {
                    bool resultThread;
                    thread1 = std::thread([&]() {
                        resultThread = start_thread(result.first, j);
                    });
                    thread1.detach();
//                    std::cout << "resultThread1:" << resultThread << "\n";
                    if (resultThread) {
                        return true;
                    }
                    workedThreadsArray[j] = false;
                }
                if (j == 2) {
                    bool resultThread;
                    thread2 = std::thread([&]() {
                        resultThread = start_thread(result.first, j);
                    });
                    thread2.detach();
//                    std::cout << "resultThread2:" << resultThread << "\n";
                    if (resultThread) {
                        return true;
                    }
                    workedThreadsArray[j] = false;
                }
            }
        }
        return false;
    }

    bool MainService::continue_thread(std::size_t threadNumber) {
        CPU& cpu = cpuService.get_cpu();
        std::size_t it = 0;
        for (std::size_t i = cpu.get_core(threadNumber).get_current_inst();
                    i < cpu.get_program_memory().get_number(); ++i, ++it) {
            cpu.get_core(threadNumber).set_current_inst(i);
            if (breakPoints[i] && it != 0) {
                return true;
            }
            auto result = cpuService.process_instruction(cpu.get_program_memory().get_instruction(i), i, threadNumber);
            if (result.second == TypeOfInstruction::COMMAND) {
                continue;
            }
            if (result.second == TypeOfInstruction::GOTO) {
                i = result.first - 1;
                continue;
            }
            if (result.second == TypeOfInstruction::THREAD_DONE) {
                cpu.get_core(threadNumber).set_current_inst(-1);
                return false;
            }
        }
        return false;
    }

    bool MainService::continue_work() {
        CPU& cpu = cpuService.get_cpu();
        std::array<bool, 3> workedThreadsArray = {true, cpu.get_core(1).get_current_inst() != -1,
                                                  cpu.get_core(2).get_current_inst() != -1};
        std::thread thread1, thread2;
        if (workedThreadsArray[1]) {
            bool resultThread;
            thread1 = std::thread([&]() {
                resultThread = continue_thread(1);
            });
            thread1.detach();
            if (resultThread) {
                return true;
            }
            workedThreadsArray[1] = false;
        }
        if (workedThreadsArray[2]) {
            bool resultThread;
            thread2 = std::thread([&]() {
                resultThread = continue_thread(2);
            });
            thread2.detach();
            if (resultThread) {
                return true;
            }
            workedThreadsArray[2] = false;
        }
        std::size_t it = 0;
        for (std::size_t i = cpu.get_core(0).get_current_inst();
                        i < cpu.get_program_memory().get_number(); ++i, ++it) {
            cpu.get_core(0).set_current_inst(i);
            //std::cout << "index: " << i << cpu.get_program_memory().get_instruction(i)->get_instruction();
            if (breakPoints[i] && it != 0) {
                return true;
            }
            auto result = cpuService.process_instruction(cpu.get_program_memory().get_instruction(i), i, 0);
            if (result.second == TypeOfInstruction::COMMAND)
                continue;
            if (result.second == TypeOfInstruction::GOTO) {
                i = result.first - 1;
                continue;
            }
            if (result.second == TypeOfInstruction::THREAD) {
                std::size_t j;
                for (j = 1; j <= 2; ++j) {
                    if (!workedThreadsArray[j]) {
                        workedThreadsArray[j] = true;
                        break;
                    }
                }
                if (j == 1) {
                    bool resultThread;
                    thread1 = std::thread([&]() {
                        resultThread = start_thread(result.first, j);
                    });
                    thread1.detach();
                    if (resultThread) {
                        return true;
                    }
                    workedThreadsArray[j] = false;
                }
                if (j == 2) {
                    bool resultThread;
                    thread2 = std::thread([&]() {
                        resultThread = start_thread(result.first, j);
                    });
                    thread2.detach();
                    if (resultThread) {
                        return true;
                    }
                    workedThreadsArray[j] = false;
                }
            }
        }
        return false;
    }

    std::string MainService::show_program_memory() {
        std::string result;
        for (std::size_t i = 0; i < cpuService.get_cpu().get_program_memory().get_number(); ++i) {
            result += cpuService.get_cpu().get_program_memory().get_instruction(i)->get_instruction();
        }
        return result;
    }

    std::string MainService::show_data_memory() {
        std::string result = cpuService.get_cpu().get_data_memory().get_data();
        return result;
    }

    std::string MainService::show_registres() {
        std::string result;
        for (const auto& element: cpuService.get_cpu().get_registers()) {
            result += element.first.get_operand();
        }
        return result;
    }

    const std::string &MainService::get_name() const {
        return cpuService.get_name();
    }

    std::size_t MainService::get_size_data() {
        return cpuService.get_cpu().get_data_memory().get_size();
    }

    const std::vector<bool> &MainService::get_breakpoints() const {
        return breakPoints;
    }
}
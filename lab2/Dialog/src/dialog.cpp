//
// Created by romka on 18.09.2023.
//
#include "../include/Dialog/dialog.h"

namespace Dialog {

    void printMenu(std::string arrayOfMsgs[], int size) {
        for (int i = 0; i < size; ++i)
            std::cout << arrayOfMsgs[i] << std::endl;
    }

    void push(Queue &queue) {
        std::cout << "Enter new message:" << std::endl;
        Message message;
        std::cin >> message;

        if (std::cin.eof()) {
            throw std::runtime_error("Failed to read: EOF\n");
        } else if (std::cin.bad()) {
            throw std::runtime_error("Input broken\n");
        }  else if (!std::cin.good()) {
            std::cout << "Input error" << std::endl;
        } else {
            queue += message;
            std::cout << "Push was successfully" << std::endl;
        }
    }

    void pop(Queue &queue) {
        try {
            Message message = --queue;
            std::cout << "Your message:" << std::endl << message;
        }
        catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }

    void check(Queue &queue) {
        Queue::outputState(std::cout, queue.checkState());
    }

    void reorganization(Queue &queue) {
        queue.reorganizationQueue();
        std::cout << "Reorganization was successfully" << std::endl;
    }

    void output(Queue &queue) {
        std::cout << "Your queue:" << std::endl << queue;
    }

    void sort(Queue &queue) {
        queue.orderByChat();
        std::cout << "Queue was sorted" << std::endl;
    }

    void getMessagesFromChat(Queue &queue) {
        std::string chatName;
        std::cout << "Enter chat name:" << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, chatName);

        if (std::cin.eof()) {
            throw std::runtime_error("Failed to read: EOF\n");
        } else if (std::cin.bad()) {
            throw std::runtime_error("Input broken\n");
        } else {
            Queue queueResult = queue[chatName];
            std::cout << "Your queue:" << std::endl << queueResult;
        }
    }

    void findMessage(Queue &queue) {
        std::string word;
        std::cout << "Enter searched word:" << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, word);

        if (std::cin.eof()) {
            throw std::runtime_error("Failed to read: EOF\n");
        } else if (std::cin.bad()) {
            throw std::runtime_error("Input broken\n");
        } else {

            try {
                Message result = queue.searchMessage(word);
                std::cout << "Your message:" << std::endl << result;
            }
            catch (const std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    Queue create(int size, Message array[]) {
        std::cout << "How do you want to create the queue?" << std::endl;
        std::string msgs[] = {"1. Create empty queue",
                              "2. Create queue with array of messages",
                              "3. Input queue"};
        printMenu(msgs, 3);
        try {
            int option = getNum(1, 3);
            switch (option) {
                case 1 : {
                    return {};
                }
                case 2 : {
                    return {size, array};
                }
                case 3 : {
                    Queue queue;
                    std::cout << "Please enter queue size and messages in queue:" << std::endl;
                    std::cin >> queue;

                    if (std::cin.eof()) {
                        throw std::runtime_error("Failed to read: EOF\n");
                    } else if (std::cin.bad()) {
                        throw std::runtime_error("Input broken\n");
                    } else if (!std::cin.good()) {
                        std::cout << "Input error" << std::endl;
                    }
                    return queue;
                }
                default:
                    break;
            }
        }
        catch (const std::exception &e) {
            throw e;
        }
        return {};
    }

    int getNum(int min, int max) {
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        int number;
        while (true) {
            std::cin >> number;

            if (std::cin.eof()) {
                throw std::runtime_error("Failed to read number: EOF\n");
            } else if (std::cin.bad()) {
                throw std::runtime_error("Input error\n");
            } else if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong, repeat please!" << std::endl;
            }
            else if (number >= min && number <= max) {
                return number;
            } else {
                std::cout << "You are wrong, repeat please!" << std::endl;
            }
        }
    }
}
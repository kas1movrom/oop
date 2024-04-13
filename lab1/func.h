//
// Created by romka on 07.09.2023.
//

#ifndef LAB1VERSION3OOP_FUNC_H
#define LAB1VERSION3OOP_FUNC_H

#include <iostream>
#include <limits>
#include <string>
#include <cstring>
#include <cmath>

namespace Lab1 {

    struct Item {
        int i, j;
        int value;
    };

    struct Matrix {
        int rows = 0;
        int cols = 0;

        int size = 0;
        int capacity = 2;
        Item *array = new Item[capacity];
    };

    template <class T>
    T getNumber(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
        T number;
        while (true) {
            std::cin >> number;
            if (std::cin.eof()) {
                throw std::runtime_error("Failed to read number: EOF\n");
            } else if (std::cin.bad()) {
                throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
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

    void push(Matrix &matrix, int i, int j, int value);

    Matrix input();

    bool criterion1(int element);
    bool criterion2(int element);

    int *individualTask(const Matrix &matrix, bool(*func)(int));

    void output(const Matrix &matrix, const int *array);
    void dopTask(const Matrix &matrix);
}

#endif //LAB1VERSION3OOP_FUNC_H

//
// Created by romka on 07.09.2023.
//
#include "func.h"

namespace Lab1 {

    void push(Matrix &matrix, int i, int j, int value) {
        if (matrix.capacity == matrix.size) {
            matrix.capacity *= 2;

            Item *result = new Item[matrix.capacity];
            std::copy(matrix.array, matrix.array + matrix.size, result);

            delete[] matrix.array;

            matrix.array = result;
        }
        matrix.array[matrix.size++] = {i, j, value};
    }

    Matrix input() {
        Matrix matrix;

        try {
            std::cout << "Enter number of lines:" << std::endl;
            matrix.rows = getNumber<int>(0);

            std::cout << "Enter number of columns:" << std::endl;
            matrix.cols = getNumber<int>(0);

            if (matrix.cols == 0)
                return matrix;

            int element;
            for (int i = 0; i < matrix.rows; ++i) {
                std::cout << "Enter " << matrix.cols << " elements for line number " << i << ":" << std::endl;

                for (int j = 0; j < matrix.cols; ++j)
                    if ((element = getNumber<int>()) != 0)
                        push(matrix, i, j, element);

            }
        }
        catch(...) {
            delete[] matrix.array;

            throw;
        }
        return matrix;
    }

    bool criterion1(int element) { // проверяет больше ли двух цифр в числе
        element = std::abs(element);
        int cnt = 0;

        while (element) {
            ++cnt;
            element /= 10;
        }
        return cnt >= 2;
    }

    bool criterion2(int element) { // проверяет простое ли число
        for (int i = 2; i <= std::sqrt(std::abs(element)); ++i)
            if (element % i == 0)
                return false;
        return true;
    }

    int *individualTask(const Matrix &matrix, bool(*func)(int)) {
        int *vector = new int[matrix.rows] ();

        for (int i = 0; i < matrix.size; ++i) {
            Item &item = matrix.array[i];

            if (func(item.value))
                vector[item.i] += item.value;
        }
        return vector;
    }

    void output(const Matrix &matrix, const int *array) {
        std::cout << "Sourced matrix:" << std::endl;

        int index = 0;
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.cols; ++j) {

                if (index < matrix.size && matrix.array[index].i == i && matrix.array[index].j == j) {
                    std::cout << matrix.array[index].value << " ";
                    ++index;
                }
                else {
                    std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }

        std::cout << "Sourced vector:" << std::endl;

        for (int i = 0; i < matrix.rows; ++i)
            std::cout << array[i] << " ";

        std::cout << std::endl;
    }

    void dopTask(const Matrix &matrix) {
        std::cout << "Sourced dop task:" << std::endl;

        int index = 0;

        for (int i = 0; i < matrix.rows; ++i) {
            int maxValue = std::numeric_limits<int>::min();

            for (int j = 0; j < matrix.cols; ++j) {

                if (index < matrix.size && matrix.array[index].i == i && matrix.array[index].j == j) {

                    if (matrix.array[index].value > maxValue) {
                        maxValue = matrix.array[index].value;
                    }
                    ++index;
                }
                else {

                    if (0 > maxValue) {
                        maxValue = 0;
                    }
                }

            }

            std::cout << maxValue << std::endl;
        }
    }
}


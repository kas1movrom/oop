#include "func.h"

using namespace Lab1;

int main() {
    Matrix matrix = {0, 0, 0, 0, nullptr};

    try {
        matrix = input();
        int *vector = individualTask(matrix, criterion1);

        output(matrix, vector);

        dopTask(matrix);

        delete[] vector;
    }
    catch (const std::bad_alloc &ba) {
        std::cerr << "Not enough memory" << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    delete[] matrix.array;

    return 0;
}

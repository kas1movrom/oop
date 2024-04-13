//
// Created by romka on 11.11.2023.
//
#include "String.h"
#include <vector>
#include <string>
#include <cstdio>


using namespace MyFpmiString;

int main() {
    std::vector<char> vec;

    char symbol;
    do {
        symbol = static_cast<char>(getchar());
        vec.push_back(symbol);
    } while (symbol != ' ');
    for (auto x: vec) {
        std::cout << x;
    }
}
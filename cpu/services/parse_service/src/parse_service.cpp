//
// Created by romka on 13.12.2023.
//
#include <iostream>
#include "../include/parse_service.h"

namespace cpu {

    std::deque<ParseService::DequeType> ParseService::parse_file(std::ifstream &inStream) {
        //std::cout << "I am in parse_file parseService\n";
        std::deque<ParseService::DequeType> result;
        std::string curLine;
        while (std::getline(inStream, curLine) && curLine != "section programMemory") {
            if (curLine == "section dataMemory" || curLine.empty())
                continue;
            result.push_back(parse_line_data(curLine));
        }
        while (std::getline(inStream, curLine)) {
            if (curLine.empty())
                continue;
            result.push_back(parse_line_instruction(curLine));
        }
//        std::cout << "Your deque:\n";
//        for (const auto& element: result) {
//            std::cout << "\t";
//            for (const auto& str: element.first) {
//                std::cout << str << " ";
//            }
//            std::cout << "\n";
//        }
        return result;
    }

    ParseService::DequeType ParseService::parse_line_data(const std::string &line) {
        std::size_t position = line.find(' ', 5);
        return std::make_pair(std::vector<std::string>
                ({line.substr(4, position - 4), line.substr(position + 1)})
                              , std::make_pair(true, false));
    }

    ParseService::DequeType ParseService::parse_line_instruction(const std::string &line) {
        std::size_t position1 = line.find(':'), position2;
        std::string identifier;
        if (position1 != std::string::npos) {
            identifier = line.substr(4, position1 - 4);
            position1 += 2;
        } else {
            position1 = 4;
        }
        position2 = line.find(' ', position1);
        std::string instructionName = line.substr(position1, position2++ - position1);
        position1 = line.find(' ', position2);
        auto value = std::make_pair(false, false);
        if (position1 == std::string::npos) {
            std::string firstOperand = line.substr(position2);
            if (instructionName == "GOTO" || instructionName.find("THREAD") != std::string::npos)
                value.second = true;
            return std::make_pair(std::vector<std::string>
                    ({firstOperand, instructionName, identifier}), value);
        }
        std::string firstOperand = line.substr(position2, position1++ - position2);
        std::string secondOperand = line.substr(position1);
        return std::make_pair(std::vector<std::string>
                ({firstOperand, secondOperand, instructionName, identifier}), value);
    }

}
//
// Created by romka on 13.12.2023.
//

#ifndef CPU_FINAL_PARSE_SERVICE_H
#define CPU_FINAL_PARSE_SERVICE_H

#include <vector>
#include <fstream>
#include <deque>

namespace cpu {

    class ParseService {
    public:

        using DequeType = std::pair<std::vector<std::string>, std::pair<bool, bool>>;

    private:

        static DequeType parse_line_data(const std::string& line);
        static DequeType parse_line_instruction(const std::string& line);

    public:

        ParseService() = delete;

        static std::deque<DequeType> parse_file(std::ifstream& inStream);

    };

}

#endif //CPU_FINAL_PARSE_SERVICE_H

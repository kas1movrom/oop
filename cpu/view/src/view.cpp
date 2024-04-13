//
// Created by romka on 19.12.2023.
//
#include "../include/view.h"

namespace cpu {

    cpu::View::View() {
        runButtonTexture.loadFromFile(R"(C:\Users\romka\CLionProjects\cpu_final\images\green_arrow.png)");
        runButton.setTexture(&runButtonTexture);
        runButton.setPosition(605, 0);

        continueButtonTexture.loadFromFile(R"(C:\Users\romka\CLionProjects\cpu_final\images\orange_button.png)");
        continueButton.setTexture(&continueButtonTexture);
        continueButton.setPosition(570, 0);

        breakButtonTexture.loadFromFile(R"(C:\Users\romka\CLionProjects\cpu_final\images\red_button.png)");
        breakButton.setTexture(&breakButtonTexture);

        font.loadFromFile(R"(C:\Users\romka\CLionProjects\cpu_final\font\Raleway-SemiBold.ttf)");
        Text tmpText("", font, 12);

        textOfProgram = tmpText;
        textOfProgram.setFillColor(Color::Black);
        textOfProgram.setStyle(Text::Bold);

        textOfData = tmpText;
        textOfData.setFillColor(Color::Black);
        textOfData.setStyle(Text::Bold);
    }

    Text &cpu::View::get_data_text() {
        return textOfData;
    }

    Text &cpu::View::get_program_text() {
        return textOfProgram;
    }

    const Text &cpu::View::get_program_text() const {
        return textOfProgram;
    }

    const Text &cpu::View::get_data_text() const {
        return textOfData;
    }

    const RectangleShape &cpu::View::get_run_button() const {
        return runButton;
    }

    const RectangleShape &cpu::View::get_continue_button() const {
        return continueButton;
    }

    const RectangleShape &cpu::View::get_break_button() const {
        return breakButton;
    }

    cpu::View &cpu::View::set_text_of_program(const std::string &filename) {
        std::ifstream inStream(filename);
        std::string content((std::istreambuf_iterator<char>(inStream)), (std::istreambuf_iterator<char>()));
        textOfProgram.setString(content);
        return *this;
    }

    cpu::View &cpu::View::set_position_text_program(float x, float y) {
        textOfProgram.setPosition(20, 10);
        return *this;
    }

    cpu::View &cpu::View::set_text_of_data(const std::string &programData) {
        textOfData.setString(programData);
        return *this;
    }

    cpu::View &cpu::View::set_position_text_data(float x, float y) {
        textOfData.setPosition(x, y);
        return *this;
    }

    View &cpu::View::set_run_red() {
        runButton.setFillColor(Color::Red);
        return *this;
    }
}
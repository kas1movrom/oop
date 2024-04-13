//
// Created by romka on 19.12.2023.
//
#include "../include/controller.h"

namespace cpu {

    Controller::Controller(std::string filename, const std::string &name):
                            filename(std::move(filename)), service(name) {
        service.fill_program(this->filename);
    }

    void Controller::execute() {
        RenderWindow mainWindow(VideoMode(640, 480), service.get_name(), Style::Fullscreen);
        view.set_text_of_program(filename).set_position_text_program(20, 10);
        view.set_position_text_data(200, 10);
        std::size_t cntRun = 0;

//        service.set_breakpoint(4);
//        service.set_breakpoint(14);

        bool resultOfProgram = false;

        int start = 68 + static_cast<int>(service.get_size_data() * 12);
        std::vector<RectangleShape> breakButtons;

        while (mainWindow.isOpen()) {
            Event event;
            Vector2i mousePos = Mouse::getPosition(mainWindow);
            while (mainWindow.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    mainWindow.close();
                }
                if (event.type == Event::MouseButtonPressed) {
                    if (view.get_run_button().getGlobalBounds().contains(mousePos.x, mousePos.y) && cntRun == 0) {
                        resultOfProgram = service.start_program();
                        view.set_text_of_data(service.show_registres() + service.show_data_memory());
                        view.set_run_red();
                        ++cntRun;
                    }
                    if (view.get_continue_button().getGlobalBounds().contains(mousePos.x, mousePos.y)
                            && cntRun != 0 && resultOfProgram) {
                        resultOfProgram = service.continue_work();
                        view.set_text_of_data(service.show_registres() + service.show_data_memory());
                        ++cntRun;
                    }
                    if (cntRun == 0 && mousePos.x < 19) {
                        breakButtons.push_back(view.get_break_button());
                        std::size_t index = (mousePos.y - start) / 14;
                        breakButtons.back().setPosition(10, start + index * 14);
                        service.set_breakpoint(index);
                    }
                }
            }
//            if (cntRun == 0) {
//                if (Keyboard::isKeyPressed(Keyboard::Num0)) {
//                    service.set_breakpoint(0);
////                    breakButtons.push_back(view.get_break_button());
////                    breakButtons.back().setPosition(10, start);
//                } else if (Keyboard::isKeyPressed(Keyboard::Num1)) {
//                    set_keyboard_button(1, breakButtons, start);
//                } else if (Keyboard::isKeyPressed(Keyboard::Num2)) {
//                    set_keyboard_button(2, breakButtons, start);
//                } else if (Keyboard::isKeyPressed(Keyboard::Num3)) {
//                    set_keyboard_button(3, breakButtons, start);
//                } else if (Keyboard::isKeyPressed(Keyboard::Num4)) {
//                    std::cout << "in 4\n";
//                    set_keyboard_button(4, breakButtons, start);
//                } else if (Keyboard::isKeyPressed(Keyboard::Num5)) {
//                    set_keyboard_button(5, breakButtons, start);
//                } else if (Keyboard::isKeyPressed(Keyboard::Num6)) {
//                    set_keyboard_button(6, breakButtons, start);
//                } else if (Keyboard::isKeyPressed(Keyboard::Num7)) {
//                    set_keyboard_button(7, breakButtons, start);
//                } else if (Keyboard::isKeyPressed(Keyboard::Num8)) {
//                    set_keyboard_button(8, breakButtons, start);
//                } else if (Keyboard::isKeyPressed(Keyboard::Num9)) {
//                    set_keyboard_button(9, breakButtons, start);
//                }
//            }
            mainWindow.clear(Color::White);

            if (resultOfProgram || cntRun == 0) {
                mainWindow.draw(view.get_continue_button());
            }
            for (const auto& element: breakButtons) {
                mainWindow.draw(element);
            }
            mainWindow.draw(view.get_run_button());
            mainWindow.draw(view.get_program_text());
            mainWindow.draw(view.get_data_text());
            mainWindow.display();
        }
        for (auto element: service.get_breakpoints()) {
            std::cout << element << "\n";
        }
    }

    void Controller::set_keyboard_button(std::size_t firstDigit, std::vector<RectangleShape>& buttons,
                                         int start) {
        std::size_t target = firstDigit * 10;
//        buttons.push_back(view.get_break_button());
        if (Keyboard::isKeyPressed(Keyboard::Num0)) {
            service.set_breakpoint(target);
        } else if (Keyboard::isKeyPressed(Keyboard::Num1)) {
//            target += 1;
            service.set_breakpoint(target + 1);
        } else if (Keyboard::isKeyPressed(Keyboard::Num2)) {
//            target += 2;
            service.set_breakpoint(target + 2);
        } else if (Keyboard::isKeyPressed(Keyboard::Num3)) {
//            target += 3;
            service.set_breakpoint(target + 3);
        } else if (Keyboard::isKeyPressed(Keyboard::Num4)) {
//            target += 4;
            service.set_breakpoint(target + 4);
        } else if (Keyboard::isKeyPressed(Keyboard::Num5)) {
//            target += 5;
            service.set_breakpoint(target + 5);
        } else if (Keyboard::isKeyPressed(Keyboard::Num6)) {
//            target += 6;
            service.set_breakpoint(target + 6);
        } else if (Keyboard::isKeyPressed(Keyboard::Num7)) {
//            target += 7;
            service.set_breakpoint(target + 7);
        } else if (Keyboard::isKeyPressed(Keyboard::Num8)) {
//            target += 8;
            service.set_breakpoint(target + 8);
        } else if (Keyboard::isKeyPressed(Keyboard::Num9)) {
//            target += 9;
            service.set_breakpoint(target + 9);
        } else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
//            target /= 10;
            service.set_breakpoint(target / 10);
        }
//        service.set_breakpoint(target);
//        buttons.back().setPosition(10, static_cast<float>(start) + static_cast<float>(target) * 12);
    }
}
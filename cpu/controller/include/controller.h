//
// Created by romka on 19.12.2023.
//

#ifndef CPU_FINAL_CONTROLLER_H
#define CPU_FINAL_CONTROLLER_H

#include "../../services/main_service/include/main_service.h"
#include "../../view/include/view.h"

namespace cpu {

    class Controller {

    private:

        MainService service;
        cpu::View view;
        std::string filename;

        void set_keyboard_button(std::size_t firstDigit, std::vector<RectangleShape>& buttons, int start);

    public:

        Controller(std::string filename, const std::string& name);

        void execute();
    };

}

#endif //CPU_FINAL_CONTROLLER_H

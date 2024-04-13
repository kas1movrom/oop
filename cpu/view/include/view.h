//
// Created by romka on 19.12.2023.
//

#ifndef CPU_FINAL_VIEW_H
#define CPU_FINAL_VIEW_H

#include <SFML/Graphics.hpp>

#include <fstream>

using namespace sf;

namespace cpu {

    class View {

    private:

        RectangleShape runButton = RectangleShape(Vector2f(35, 35));
        RectangleShape continueButton = RectangleShape(Vector2f(35, 35));
        RectangleShape breakButton = RectangleShape(Vector2f(14, 14));

        Text textOfProgram;
        Text textOfData;

        Texture runButtonTexture;
        Texture continueButtonTexture;
        Texture breakButtonTexture;

        Font font;

    public:

        View();

        Text& get_program_text();
        [[nodiscard]] const Text& get_program_text() const;

        Text& get_data_text();
        [[nodiscard]] const Text& get_data_text() const;

        [[nodiscard]] const RectangleShape& get_run_button() const;

        [[nodiscard]] const RectangleShape& get_continue_button() const;

        [[nodiscard]] const RectangleShape& get_break_button() const;

        View& set_text_of_program(const std::string& filename);
        View& set_position_text_program(float x, float y);

        View& set_run_red();

        View& set_text_of_data(const std::string& programData);
        View& set_position_text_data(float x, float y);
    };

}

#endif //CPU_FINAL_VIEW_H

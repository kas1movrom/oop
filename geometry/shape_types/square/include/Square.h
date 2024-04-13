//
// Created by romka on 21.11.2023.
//

#ifndef GEOM_MFTI_SQUARE_H
#define GEOM_MFTI_SQUARE_H

#include "../../rectangle/include/Rectangle.h"
#include "../../circle/include/Circle.h"

namespace MyFpmiGeometry {

    class Square:
            public Rectangle {

    public:

        Square(const Point& center1, const Point& center2);

        [[nodiscard]] double side() const;

        [[nodiscard]] double first_side() const final;

        [[nodiscard]] double second_side() const final;

        [[nodiscard]] double diagonal() const final;

        [[nodiscard]] Circle circumscribed_circle() const;

        [[nodiscard]] Circle inscribed_circle() const;

    };

}

#endif //GEOM_MFTI_SQUARE_H

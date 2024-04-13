//
// Created by romka on 21.11.2023.
//

#ifndef GEOM_MFTI_SHAPE_H
#define GEOM_MFTI_SHAPE_H

#include "../../point/include/Point.h"

namespace MyFpmiGeometry {

    class Shape {

    public:

        [[nodiscard]] virtual Point center() const = 0;

        [[nodiscard]] virtual double perimeter() const = 0;

        [[nodiscard]] virtual double area() const = 0;


        virtual Shape& translate(const Point& new_center) = 0;

        virtual Shape& rotate(double angle) = 0;

        virtual Shape& scale(double coefficient) = 0;


    };

}

#endif //GEOM_MFTI_SHAPE_H

//
// Created by romka on 21.11.2023.
//

#ifndef GEOM_MFTI_RECTANGLE_H
#define GEOM_MFTI_RECTANGLE_H

#include "../../../interface/include/Shape.h"

#include <iostream>
#include <vector>

namespace MyFpmiGeometry {

    class Rectangle:
            public Shape {

    protected:

        double length;

        Point a;
        Point b;

    public:

        Rectangle(double length, const Point& a, const Point& b);

        [[nodiscard]] Point center() const final;

        [[nodiscard]] double perimeter() const final;

        [[nodiscard]] double area() const override;

        Shape& translate(const Point& new_center) final;

        Shape& rotate(double angle) final;

        Shape& scale(double coefficient) final;

        [[nodiscard]] virtual double first_side() const;

        [[nodiscard]] virtual double second_side() const;

        [[nodiscard]] virtual double diagonal() const;

        [[nodiscard]] std::vector<Point> vertices() const;
    };

}

#endif //GEOM_MFTI_RECTANGLE_H

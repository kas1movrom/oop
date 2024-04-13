//
// Created by romka on 21.11.2023.
//

#ifndef GEOM_MFTI_TRIANGLE_H
#define GEOM_MFTI_TRIANGLE_H

#include "../../../interface/include/Shape.h"
#include "../../circle/include/Circle.h"

namespace MyFpmiGeometry {

    class Triangle:
            public Shape {

    private:

        Point a, b, c;

    public:

        Triangle(const Point& p1, const Point& p2, const Point& p3);

        [[nodiscard]] std::vector<Point> vertices() const;

        [[nodiscard]] Point center() const final;

        [[nodiscard]] double perimeter() const final;

        [[nodiscard]] double area() const final;

        Shape& translate(const Point& new_center) final;

        Shape& rotate(double angle) final;

        Shape& scale(double coefficient) final;

        [[nodiscard]] Circle circumscribed_circle() const;

        [[nodiscard]] Circle inscribed_circle() const;

        [[nodiscard]] Point orthocenter() const;

    };

}

#endif //GEOM_MFTI_TRIANGLE_H

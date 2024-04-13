//
// Created by romka on 21.11.2023.
//

#ifndef GEOM_MFTI_ELLIPSE_H
#define GEOM_MFTI_ELLIPSE_H

#include "../../../interface/include/Shape.h"

#include <vector>

namespace MyFpmiGeometry {

    class Ellipse:
            public Shape {

    protected:

        Point a;
        Point b;
        double periFocusLength;

    public:

        Ellipse(const Point& p1, const Point& p2, double distance);

        [[nodiscard]] virtual std::vector<Point> focuses() const;

        [[nodiscard]] virtual double focal_distance() const;

        [[nodiscard]] virtual double major_semi_axis() const;

        [[nodiscard]] virtual double minor_semi_axis() const;

        [[nodiscard]] virtual double eccentricity() const;

        [[nodiscard]] Point center() const override;

        [[nodiscard]] double perimeter() const final;

        [[nodiscard]] double area() const final;

        Shape& translate(const Point& new_center) final;

        Shape& rotate(double angle) override;

        Shape& scale(double coefficient) override;
    };

}

#endif //GEOM_MFTI_ELLIPSE_H

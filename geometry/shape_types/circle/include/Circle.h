//
// Created by romka on 21.11.2023.
//

#ifndef GEOM_MFTI_CIRCLE_H
#define GEOM_MFTI_CIRCLE_H

#include "../../ellipse/include/Ellipse.h"

namespace MyFpmiGeometry {

    class Circle:
            public Ellipse {

    public:

        Circle(const Point& cent, double radius);

        [[nodiscard]] double radius() const;

        [[nodiscard]] std::vector<Point> focuses() const final;

        [[nodiscard]] double focal_distance() const final;

        [[nodiscard]] double major_semi_axis() const final;

        [[nodiscard]] double minor_semi_axis() const final;

        [[nodiscard]] double eccentricity() const final;

        [[nodiscard]] Point center() const final;

        Shape& rotate(double angle) final;

        Shape& scale(double coefficient) final;

    };

}

#endif //GEOM_MFTI_CIRCLE_H

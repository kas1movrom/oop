//
// Created by romka on 21.11.2023.
//
#include "../include/Square.h"

namespace MyFpmiGeometry {

    Square::Square(const Point &center1, const Point &center2): Rectangle(center1.distance(center2),
                                                                          center1, center2) {}

    double Square::side() const {
        return length;
    }

    double Square::second_side() const {
        return length;
    }

    double Square::first_side() const {
        return length;
    }

    double Square::diagonal() const {
        return length * sqrt(2);
    }

    Circle Square::circumscribed_circle() const {
        Circle result(center(), diagonal() / 2);
        return result;
    }

    Circle Square::inscribed_circle() const {
        Circle result(center(), length / 2);
        return result;
    }
}

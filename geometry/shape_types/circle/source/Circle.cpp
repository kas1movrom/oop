//
// Created by romka on 21.11.2023.
//
#include "../include/Circle.h"

namespace MyFpmiGeometry {

    Circle::Circle(const Point &cent, double radius): Ellipse(cent, cent, radius) {}

    double Circle::radius() const {
        return periFocusLength;
    }

    double Circle::focal_distance() const {
        return 0.0;
    }

    std::vector<Point> Circle::focuses() const {
        std::vector<Point> result = {a};
        return result;
    }

    double Circle::eccentricity() const {
        return 0.0;
    }

    double Circle::major_semi_axis() const {
        return periFocusLength;
    }

    double Circle::minor_semi_axis() const {
        return periFocusLength;
    }

    Point Circle::center() const {
        Point center = a;
        return center;
    }

    Shape &Circle::rotate(double angle) {
        return *this;
    }

    Shape &Circle::scale(double coefficient) {
        if (coefficient <= 0) {
            throw std::invalid_argument("CircleInvalidArgument");
        }
        periFocusLength * coefficient;
        return *this;
    }
}
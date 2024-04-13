//
// Created by romka on 21.11.2023.
//
#include "../include/Ellipse.h"

namespace MyFpmiGeometry {

    Ellipse::Ellipse(const Point &p1, const Point &p2, double distance): a(p1), b(p2) {
        if (distance <= 0) {
            throw std::invalid_argument("EllipseInvalidArgument");
        }
        periFocusLength = distance;
    }

    std::vector<Point> Ellipse::focuses() const {
        std::vector<Point> result = {a, b};
        return result;
    }

    double Ellipse::focal_distance() const {
        return (a.distance(b) / 2);
    }

    Point Ellipse::center() const {
        Point result = Point::get_center(a, b);
        return result;
    }

    double Ellipse::area() const {
        return M_PI * major_semi_axis() * minor_semi_axis();
    }

    double Ellipse::perimeter() const {
        double minor = minor_semi_axis();
        double major = major_semi_axis();
        double result = 4 * (M_PI * major * minor + (major - minor) * (major - minor)) / (major + minor);
        return result;
    }

    Shape &Ellipse::translate(const Point &new_center) {
        Point tmp = new_center - center();
        a += tmp;
        b += tmp;
        return *this;
    }

    Shape &Ellipse::rotate(double angle) {
        Point cen = center();
        a.operation_relative(cen, angle, true);
        b.operation_relative(cen, angle, true);
        return *this;
    }

    Shape &Ellipse::scale(double coefficient) {
        if (coefficient <= 0) {
            throw std::invalid_argument("EllipseInvalidArgument");
        }
        Point cen = center();
        a.operation_relative(cen, coefficient, false);
        b.operation_relative(cen, coefficient, false);
        periFocusLength *= coefficient;
        return *this;
    }

    double Ellipse::major_semi_axis() const {
        return focal_distance() + periFocusLength;
    }

    double Ellipse::eccentricity() const {
        return focal_distance() / major_semi_axis();
    }

    double Ellipse::minor_semi_axis() const {
        double e = eccentricity();
        return major_semi_axis() * sqrt(1 - e * e);
    }

}
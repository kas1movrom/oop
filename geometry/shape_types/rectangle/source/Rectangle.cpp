//
// Created by romka on 21.11.2023.
//
#include "../include/Rectangle.h"

namespace MyFpmiGeometry {

    Rectangle::Rectangle(double length, const Point &a, const Point &b): a(a), b(b) {
        if (length < 0.0) {
            throw std::invalid_argument("RectangleInvalidArgument");
        }
        this->length = length;
    }

    double Rectangle::first_side() const {
        return length;
    }

    double Rectangle::second_side() const {
        return a.distance(b);
    }

    double Rectangle::diagonal() const {
        double sec_side = second_side();
        return sqrt(length * length + sec_side * sec_side);
    }

    double Rectangle::perimeter() const {
        return 2 * length + 2 * second_side();
    }

    double Rectangle::area() const {
        return length * second_side();
    }

    Point Rectangle::center() const {
        return Point::get_center(a, b);
    }

    Shape &Rectangle::translate(const Point &new_center) {
        Point tmp = new_center - center();
        a += tmp;
        b += tmp;
        return *this;
    }

    Shape &Rectangle::rotate(double angle) {
        Point cen = center();
        a.operation_relative(cen, angle, true);
        b.operation_relative(cen, angle, true);
        return *this;
    }

    Shape &Rectangle::scale(double coefficient) {
        if (coefficient <= 0) {
            throw std::invalid_argument("RectangleInvalidArgument");
        }
        Point cen = center();
        a.operation_relative(cen, coefficient, false);
        b.operation_relative(cen, coefficient, false);
        length *= coefficient;
        return *this;
    }

    std::vector<Point> Rectangle::vertices() const {
        Point cen = center(), first = a.relative_point(cen), second = b.relative_point(cen);
        double angle = atan((length / 2) / (second_side() / 2)), kef = diagonal() / second_side();
        first.rotate(angle);
        second.rotate(angle);
        first *= kef;
        second *= kef;
        Point p1 = cen + first, p3 = cen + second;
        std::vector<Point> result = {p1, Point::dot_product(2 * b.get_x() - p3.get_x(), 2 * b.get_y() - p3.get_y()),
                                     p3, Point::dot_product(2 * a.get_x() - p1.get_x(), 2 * a.get_y() - p1.get_y())};
        return result;
    }
}

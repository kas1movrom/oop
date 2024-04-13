//
// Created by romka on 21.11.2023.
//
#include "../include/Triangle.h"

namespace MyFpmiGeometry {

    Triangle::Triangle(const Point &p1, const Point &p2, const Point &p3): a(p1), b(p2), c(p3) {}

    std::vector<Point> Triangle::vertices() const {
        std::vector<Point> result = {a, b, c};
        return result;
    }

    double Triangle::perimeter() const {
        return a.distance(b) + b.distance(c) + c.distance(a);
    }

    double Triangle::area() const {
        double per = perimeter() / 2;
        return sqrt(per * (per - a.distance(b)) * (per - b.distance(c)) * (per - c.distance(a)));
    }

    Point Triangle::center() const {
        return Point::dot_product((a.get_x() + b.get_x() + c.get_x()) / 3, (a.get_y() + b.get_y() + c.get_y()) / 3);
    }

    Shape &Triangle::translate(const Point &new_center) {
        Point tmp = new_center - center();
        a += tmp;
        b += tmp;
        c += tmp;
        return *this;
    }

    Shape &Triangle::rotate(double angle) {
        Point cen = center();
        a.operation_relative(cen, angle, true);
        b.operation_relative(cen, angle, true);
        c.operation_relative(cen, angle, true);
        return *this;
    }

    Shape &Triangle::scale(double coefficient) {
        if (coefficient <= 0) {
            throw std::invalid_argument("TriangleInvalidArgument");
        }
        Point cen = center();
        a.operation_relative(cen, coefficient, false);
        b.operation_relative(cen, coefficient, false);
        c.operation_relative(cen, coefficient, false);
        return *this;
    }

    Point Triangle::orthocenter() const {
        Point first = a - b, second = b - c;
        return Point::intersection_lines(first.get_x(), first.get_y(), c.scalar_product(-first),
                                         second.get_x(), second.get_y(), a.scalar_product(-second));
    }

    Circle Triangle::circumscribed_circle() const {
        Point cen1 = Point::get_center(a, b), cen2 = Point::get_center(b, c);
        Point first = a - b, second = b - c;
        double rad = (a.distance(b) * b.distance(a) * c.distance(a)) / (4 * area());
        Circle result(Point::intersection_lines(first.get_x(), first.get_y(), cen1.scalar_product(-first),
                                                second.get_x(), second.get_y(), cen2.scalar_product(-second)), rad);
        return result;
    }

    Circle Triangle::inscribed_circle() const {
        Point m1 = Point::regarding_point(a.distance(c) / b.distance(c), a, b);
        Point m2 = Point::regarding_point(a.distance(c) / b.distance(a), c, c);
        double rad = 2 * area() / perimeter();
        Point first = m1 - c, second = m2 - a;
        first.rotate_y();
        second.rotate_y();
        Circle result(Point::intersection_lines(first.get_y(), first.get_x(), m1.get_y() * (-first.get_x()) -
            m1.get_x() * first.get_y(), second.get_y(), second.get_x(), m2.get_y()
            * (-second.get_x()) - m2.get_x() * second.get_y()), rad);
        return result;
    }
}
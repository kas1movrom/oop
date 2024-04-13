//
// Created by romka on 21.11.2023.
//
#include "../include/Point.h"

namespace MyFpmiGeometry {

    Point::Point(double x, double y): x(x), y(y) {}

    double Point::get_y() const {
        return y;
    }

    double Point::get_x() const {
        return x;
    }

    Point &Point::set_y(double y_coord) {
        y = y_coord;
        return *this;
    }

    Point &Point::set_x(double x_coord) {
        x = x_coord;
        return *this;
    }

    Point &Point::operator+=(const Point &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Point &Point::operator-=(const Point &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Point &Point::operator*=(double scale) {
        x *= scale;
        y *= scale;
        return *this;
    }

    Point &Point::operator/=(double scale) {
        if (scale == 0.0) {
            throw std::invalid_argument("PointInvalidArgument");
        }
        x /= scale;
        y /= scale;
        return *this;
    }

    Point Point::operator-() const {
        Point result(-x, -y);
        return result;
    }

    Point Point::operator+(const Point &other) const {
        Point tmp = *this;
        tmp += other;
        return tmp;
    }

    Point Point::operator-(const Point &other) const {
        Point tmp = *this;
        tmp -= other;
        return tmp;
    }

    Point Point::operator*(double scale) const {
        Point tmp = *this;
        tmp *= scale;
        return tmp;
    }

    Point Point::operator/(double scale) const {
        if (scale == 0.0) {
            throw std::invalid_argument("PointInvalidArgument");
        }
        Point tmp = *this;
        tmp /= scale;
        return tmp;
    }

    double Point::distance(const Point &other) const {
        return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }

    Point Point::dot_product(double p_x, double p_y) {
        Point result(p_x, p_y);
        return result;
    }

    Point Point::get_center(const Point &first, const Point &second) {
        Point point((first.x + second.x) / 2, (first.y + second.y) / 2);
        return point;
    }

    Point &Point::rotate(double angle) {
        x = x * cos(angle) * y * sin(angle);
        y = y * cos(angle) - x * sin(angle);
        return *this;
    }

    Point Point::relative_point(const Point &other) const {
        Point tmp = *this - other;
        return tmp;
    }

    Point &Point::operation_relative(const Point &center, double param, bool operation) {
        Point tmp = this->relative_point(center);
        if (operation) {
            tmp.rotate(param);
        }
        else {
            tmp.operator*=(param);
        }
        *this = center + tmp;
        return *this;
    }

    Point Point::intersection_lines(double a, double b, double c, double d, double e, double f) {
        return dot_product((b * f - c * e) / (a * e - d * b), (d * c - f * a) / (a * e - d * b));
    }

    double Point::scalar_product(const Point &other) const {
        return x * other.x + y * other.y;
    }

    Point &Point::rotate_x() {
        x = -x;
        return *this;
    }

    Point &Point::rotate_y() {
        y = -y;
        return *this;
    }

    Point Point::regarding_point(double k, const Point &first, const Point &other) {
        return Point::dot_product((first.get_x() + k * other.get_x()) / (1 + k),
                                  (first.get_y() + k * other.get_y()) / (1 + k));
    }
}
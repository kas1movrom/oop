//
// Created by romka on 21.11.2023.
//

#ifndef GEOM_MFTI_POINT_H
#define GEOM_MFTI_POINT_H

#include <iostream>
#include <cmath>

namespace MyFpmiGeometry {

    class Point {

    private:

        double x;
        double y;

        explicit Point(double x = 0.0, double y = 0.0);

    public:

        [[nodiscard]] double get_x() const;

        [[nodiscard]] double get_y() const;

        Point& set_x(double x_coord);

        Point& set_y(double y_coord);

        Point& operator+=(const Point& other);

        Point& operator-=(const Point& other);

        Point& operator*=(double scale);

        Point& operator/=(double scale);

        Point operator-() const;

        Point operator-(const Point& other) const;

        Point operator+(const Point& other) const;

        Point operator*(double scale) const;

        Point operator/(double scale) const;

        [[nodiscard]] double distance(const Point& other = Point()) const;

        static Point dot_product(double p_x = 0.0, double p_y = 0.0);

        static Point intersection_lines(double a, double b, double c, double d, double e, double f);

        static Point get_center(const Point& first, const Point& second);

        Point& rotate(double angle);

        [[nodiscard]] Point relative_point(const Point& other) const;

        Point& operation_relative(const Point& center, double param, bool operation);

        [[nodiscard]] double scalar_product(const Point& other) const;

        Point& rotate_x();

        Point& rotate_y();

        static Point regarding_point(double k, const Point& first, const Point& other);
    };

}

#endif //GEOM_MFTI_POINT_H

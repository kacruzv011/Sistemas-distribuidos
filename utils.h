#ifndef UTILS_H
#define UTILS_H

#include <iostream>

struct Vector2D {
    double x, y;

    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& v) const {
        return Vector2D(x + v.x, y + v.y);
    }

    Vector2D operator-(const Vector2D& v) const {
        return Vector2D(x - v.x, y - v.y);
    }

    Vector2D operator*(double escalar) const {
        return Vector2D(x * escalar, y * escalar);
    }

    Vector2D operator/(double escalar) const {
        return Vector2D(x / escalar, y / escalar);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};

#endif

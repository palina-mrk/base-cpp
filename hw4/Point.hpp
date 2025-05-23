#pragma once
#include <cmath>
#include <istream>

class Point {
  public:
    double x{};
    double y{};
    Point() = default;
    ~Point() = default;
    Point(const Point& p): x{p.x}, y{p.y} {}
    Point& operator=(const Point& p) {
        x = p.x;
        y = p.y;
        return *this;
    }
    inline Point(double x, double y) : x{x}, y{y} {};
};

inline Point operator-(const Point& lhs, const Point& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

inline Point operator+(const Point& lhs, const Point& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

inline Point operator*(const Point& p, double scalar) {
    return {p.x * scalar, p.y * scalar};
}

inline Point operator/(const Point& p, double scalar) {
    return {p.x / scalar, p.y / scalar};
}

inline std::istream& operator>>(std::istream& stream, Point& p){
    stream >> p.x;
    stream >> p.y;
    return stream;
}

inline double distance2(const Point& lhs, const Point& rhs) {
    const Point delta = lhs - rhs;
    return delta.x * delta.x + delta.y * delta.y;
}

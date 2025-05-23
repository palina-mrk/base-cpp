#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
private:
    Point     center;
    Velocity  velocity;
    double    radius;
    Color     color;
    bool      collidable;
    double    mass;
public:
    Ball(double x, double y, double vx, double vy, double r,
         double red, double green, double blue, bool isColl);
    Ball(const Point& p, const Color& c, const Point& v, 
         double r, bool isColl);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool isCollidable() const;
};

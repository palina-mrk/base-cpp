#include "Ball.hpp"
#include <cmath>

/* Конструктор */
Ball::Ball(double x, double y, double vx, double vy, double r,
           double red, double green, double blue, bool isColl) 
           : center{x, y}, velocity{Point{vx,vy}},  
             collidable{isColl} {
    radius = r;
    mass =  3.14*radius*radius*radius*4.0/3.0;
    color = Color(red, green, blue);
}

Ball::Ball(const Point& p, const Color& c, const Point& v,
            double r, bool isColl): center{p}, color(c), collidable{isColl} {
   velocity.setVector(v); 
   radius = r;
   mass =  3.14*radius*radius*radius*4.0/3.0;
}
/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    this->velocity.setVector(velocity.vector()); 
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    return Velocity(this->velocity.vector());
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    painter.draw(center, radius, color);
    return;
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    this->center.x = center.x;
    this->center.y = center.y;
    return;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    return Point(center.x, center.y);
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    return radius;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    return mass;
}

/** Возвращает значение isCollidable */
bool Ball::isCollidable() const {
    return collidable;
}

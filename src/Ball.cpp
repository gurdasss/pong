#include "Ball.h"
#include <raylib.h>

// Member function definition

Ball::Ball(const Vector2 &position)
    // Member initializer list (initalized as declared in the class)
    : m_position{position}
{
    // Constructor's body is often left empty
}

const Vector2 &Ball::getPosition() const
{
    return m_position;
}

void Ball::setPosition(const Vector2 &position)
{
    m_position = position;
}

float Ball::getRadius() const
{
    return m_radius;
}

const Color &Ball::getColor() const
{
    return m_color;
}

float Ball::getSpeed() const
{
    return m_speed;
}

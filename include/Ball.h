#include <raylib.h>

#ifndef BALL_H
#define BALL_H

namespace BallConsts
{
    // inline sets the constexpr's internal to external linkage
    // so the linker will be able to de-duplicate definitions
    // of these constants
    inline constexpr float ballRadius{15};
    inline constexpr Color ballColor{BLACK};
    inline constexpr float ballSpeed{5};

} // namespace BallConstants

class Ball
{
public:
    // Member function declaration

    Ball(const Vector2 &position);

    // can safely return const l-value ref
    // because the lifetime of the data members
    // is equal to the lifetime of class type object
    const Vector2 &getPosition() const;
    void setPosition(const Vector2 &position);

    float getRadius() const;
    const Color &getColor() const;
    float getSpeed() const;

private:
    Vector2 m_position{};
    float m_radius{BallConsts::ballRadius};
    Color m_color{BallConsts::ballColor};
    float m_speed{BallConsts::ballSpeed};
};

#endif
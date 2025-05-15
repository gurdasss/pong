#include <raylib.h>

#ifndef PADDLE_H
#define PADDLE_H

namespace PaddleConsts
{
    // inline sets the constexpr's internal to external linkage
    // so the linker will be able to de-duplicate definitions
    // of these constants
    inline constexpr float paddleWidth{20};
    inline constexpr float paddleHeight{80};
    inline constexpr float paddleSpeed{4};
    inline constexpr Color paddleColor{RED};

} // namespace PaddleConstants

class Paddle
{
public:
    // Member function declaration
    Paddle(const Vector2 &position);

    void updateY(float y);
    const Color &getColor() const;
    float getSpeed() const;

    // can safely return const l-value ref
    // because the lifetime of the data members
    // is equal to the lifetime of class type object
    const Rectangle &getPaddle() const;

private:
    Rectangle m_paddle{};
    const Color m_color{PaddleConsts::paddleColor};
    const float m_speed{PaddleConsts::paddleSpeed};
};

#endif
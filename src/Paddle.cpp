#include "Paddle.h"
#include <raylib.h>
#include <assert.h>

// Member function definition

Paddle::Paddle(const Vector2 &position)
    // Member initializer list (initalized as declared in the class)
    : m_paddle{position.x, position.y,
               PaddleConsts::paddleWidth,
               PaddleConsts::paddleHeight}
{
  // Constructor's body is often left empty
}

void Paddle::updateY(float y)
{
  m_paddle.y += y;
}

float Paddle::getSpeed() const
{
  return m_speed;
}
const Rectangle &Paddle::getPaddle() const
{
  return m_paddle;
}

const Color &Paddle::getColor() const
{
  return m_color;
}

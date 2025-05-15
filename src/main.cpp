#include "Paddle.h"
#include "Ball.h"
#include "Random.h"
#include <raylib.h>

enum Direction
{
    up = -1,
    down = 1,
};

// Application specific non-member functions
// Paddle related function
void moveUp(Paddle &paddle, bool random = false);
void moveDown(Paddle &paddle, int screenHeight, bool random = false);
void drawPaddle(const Paddle &paddle);

int main()
{
    constexpr int screenWidth{800};
    constexpr int screenHeight{450};

    InitWindow(screenWidth, screenHeight, "Pong");

    SetTargetFPS(60);

    Paddle player{Vector2{screenWidth - PaddleConsts::paddleWidth, 0}};
    short playerScore{};

    Paddle computer{Vector2{0, 0}};
    short computerScore{};

    Ball ball{Vector2{
        screenWidth / 2,
        screenHeight / 2,
    }};

    while (!WindowShouldClose())
    {
        // Handle user's input
        if (IsKeyDown(KEY_UP))
            moveUp(player);

        if (IsKeyDown(KEY_DOWN))
            moveDown(player, screenHeight);

        static short s_yDirection{down};

        // Handle computer's input
        if (s_yDirection == down)
            moveDown(computer, screenHeight, true);
        else if (s_yDirection == up)
            moveUp(computer, true);

        Vector2 ballposition{ball.getPosition()};
        float ballRadius{ball.getRadius()};
        static short s_xDirection{down};

        // Handle Wall and Paddle collision
        // set X direction of ball
        // if ball hits the player, set X direction to -1
        if (CheckCollisionCircleRec(ballposition, ballRadius,
                                    player.getPaddle()))
            s_xDirection = up;
        // TODO: implement for the computer
        // if ball hits the computer, set X direction to 1
        if (CheckCollisionCircleRec(ballposition, ballRadius,
                                    computer.getPaddle()))
            s_xDirection = down;

        // set Y direction of ball
        // if ball hits the ground, set Y direction to -1
        if (ballposition.y + ballRadius > screenHeight)
            s_yDirection = up;
        // if ball hits the ceiling, set Y direction to 1
        else if (ballposition.y < 0)
            s_yDirection = down;

        // reset the ball position if it crosses
        // either side of the screen edge
        if (ballposition.x < 0 || ballposition.x > screenWidth)
        {
            // increment player's score
            // if ball is beyond left edge of the screen
            if (ballposition.x < 0)
                ++playerScore;
            else
                // increment computer's score
                // if ball is beyond right edge of the screen
                ++computerScore;

            ballposition = Vector2{
                screenWidth / 2,
                screenHeight / 2,
            };
        }

        // apply both the X and Y direction to the ball
        ballposition.x += ball.getSpeed() * s_xDirection;
        ballposition.y += ball.getSpeed() * s_yDirection;
        ball.setPosition(ballposition);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(TextFormat("%i", computerScore),
                 screenWidth / 2 - 150,
                 0,
                 50, BLACK);

        DrawText(TextFormat("%i", playerScore),
                 screenWidth / 2 + 150,
                 0,
                 50, BLACK);

        drawPaddle(player);
        drawPaddle(computer);
        DrawCircleV(ball.getPosition(), ball.getRadius(), ball.getColor());

        DrawFPS(screenWidth / 2 - 35, 0);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void moveUp(Paddle &paddle, bool random)
{

    float paddleYPos{paddle.getPaddle().y};

    // Because the Rectangle's is drawn from
    // top-left corner so its x will be
    // zero at top-left corner
    if (paddleYPos > 0)
    {
        float newYPos{paddle.getSpeed() * static_cast<float>(up)};
        float randomValue{static_cast<float>(Random::get(-5, 5))};

        if (random)
            // subtract only the 50% (0.5) from the random value
            paddle.updateY(newYPos - (0.5f * randomValue));
        else
            paddle.updateY(newYPos);
    }
}

void moveDown(Paddle &paddle, int screenHeight, bool random)
{

    float paddleYPos{paddle.getPaddle().y};
    float paddleHeight{paddle.getPaddle().height};

    // Because the Rectangle's is drawn from
    // top-left corner so its y will be
    // zero at top-left corner
    if (paddleYPos + paddleHeight <= static_cast<float>(screenHeight))
    {
        float newYPos{paddle.getSpeed() * static_cast<float>(down)};
        float randomValue{static_cast<float>(Random::get(-5, 5))};
        if (random)
            // subtract only the 50% (0.5) from the random value
            paddle.updateY(newYPos - (0.5f * randomValue));
        else
            paddle.updateY(newYPos);
    }
}

void drawPaddle(const Paddle &paddle)
{
    DrawRectangleRec(paddle.getPaddle(), paddle.getColor());
}
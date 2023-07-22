#include <iostream>
#include <raylib.h>

struct Ball
{
    float x, y;
    float speedX, speedY;
    float radius;

    void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }
};

struct Paddle
{
    float x, y;
    float speed;
    float width;
    float height;

    Rectangle GetRectangle()
    {
        return Rectangle{x - width / 2, y - height / 2, 10, 100};
    }

    void Draw()
    {
        DrawRectangleRec(GetRectangle(), WHITE);
    }
};

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib Example");

    SetWindowState(FLAG_VSYNC_HINT);

    Ball ball;
    ball.x = GetScreenWidth() / 2.0f;
    ball.y = GetScreenHeight() / 2.0f;
    ball.radius = 5;
    ball.speedX = 200;
    ball.speedY = 300;

    Paddle leftPaddle;
    leftPaddle.x = 50;
    leftPaddle.y = GetScreenHeight() / 2.0f;
    leftPaddle.width = 10;
    leftPaddle.height = 100;
    leftPaddle.speed = 500;

    Paddle rightPaddle;
    rightPaddle.x = GetScreenWidth() - 50;
    rightPaddle.y = GetScreenHeight() / 2.0f;
    rightPaddle.width = 10;
    rightPaddle.height = 100;
    rightPaddle.speed = 500;

    const char* winnerText = nullptr;
    const char* restartText = nullptr;

    // stop the window from closing until exit is pressed
    while (!WindowShouldClose())
    {
        // move the ball
        ball.x += ball.speedX * GetFrameTime();
        ball.y += ball.speedY * GetFrameTime();

        // stop ball from going out of the top of the screen
        if (ball.y < 0)
        {
            ball.y = 0;
            ball.speedY *= -1;
        }

        // stop ball from going out of the bottom of the screen
        if (ball.y > GetScreenHeight())
        {
            ball.y = GetScreenHeight();
            ball.speedY *= -1;
        }

        // move left paddle up
        // NOTE - VALUE OF 0 IS THE TOP
        if (IsKeyDown(KEY_W) && leftPaddle.y > leftPaddle.height / 2)
        {
            leftPaddle.y -= leftPaddle.speed * GetFrameTime();
        }

        // move left paddle down
        if (IsKeyDown(KEY_S) && leftPaddle.y < GetScreenHeight() - leftPaddle.height / 2)
        {
            leftPaddle.y += leftPaddle.speed * GetFrameTime();
        }

        // move right paddle up
        if (IsKeyDown(KEY_UP) && rightPaddle.y > rightPaddle.height / 2)
        {
            rightPaddle.y -= rightPaddle.speed * GetFrameTime();
        }

        // move right paddle down
        if (IsKeyDown(KEY_DOWN) && rightPaddle.y < GetScreenHeight() - rightPaddle.height / 2)
        {
            rightPaddle.y += rightPaddle.speed * GetFrameTime();
        }

        // bounce ball off left paddle
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
           leftPaddle.GetRectangle()))
        {
            if (ball.speedX < 0)
            {
                // change speed of ball
                ball.speedX *= -1.1f;
                ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2)
                    * ball.speedX;
            }
        }

        // bounce ball off red paddle
        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius,
            rightPaddle.GetRectangle()))
        {
            if (ball.speedX > 0)
            {
                // change speed of ball
                ball.speedX *= -1.1f;
                ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2)
                    * - ball.speedX;
            }
        }

        if (ball.x < 0)
        {
            winnerText = "Right Player Wins!";
        }

        if(ball.x > GetScreenWidth())
        {
            winnerText = "Left Player Wins!";
        }

        if (winnerText && IsKeyPressed(KEY_SPACE))
        {
            ball.x = GetScreenWidth() / 2;
            ball.y = GetScreenHeight() / 2;
            ball.speedX = 200;
            ball.speedY = 300;
            winnerText = nullptr;
        }

        BeginDrawing();

        ClearBackground(BLACK);
        DrawFPS(0, 0);
        ball.Draw();
        leftPaddle.Draw();
        rightPaddle.Draw();

        // check that there is a winner
        if (winnerText)
        {
        restartText = "Press [SPACE] to restart";

        int textWidth = MeasureText(winnerText, 60);
        int restartWidth = MeasureText(restartText, 30);

        DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, GREEN);
        DrawText(restartText, GetScreenWidth() / 2 - restartWidth / 2, GetScreenHeight() / 2 - 60, 30, GREEN);
        }

        EndDrawing();
    }

    CloseWindow();

	return 0;
}
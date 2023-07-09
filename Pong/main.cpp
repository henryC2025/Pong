#include <iostream>
#include <raylib.h>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib Example");

    SetTargetFPS(60);

    Rectangle rectangle{ 100, 100, 200, 150 };
    Color rectangleColor = PINK;

    while (!WindowShouldClose()) {
        if (IsKeyDown(IsKeyUp)) {
            rectangleColor = BLUE;
        }
        else {
            rectangleColor = RED;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawRectangleRec(rectangle, rectangleColor);

        EndDrawing();
    }

    CloseWindow();

	return 0;
}
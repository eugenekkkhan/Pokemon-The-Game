#include "game.h"

int main(void)
{
    InitGame();
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(WHITE);
            DrawGame();
            UpdateGame();
            
        EndDrawing();
    }
    QuitGame();
    return 0;
}
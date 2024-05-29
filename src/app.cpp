#include "game.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>
#include "pokemon.h"

int main(void)
{
    InitFile(Pokemons);
    InitGame();
    while (!WindowShouldClose())
    {
        BeginDrawing();
            rlDrawRenderBatchActive();
            Matrix proj = MatrixOrtho(0, 192*8, 108*8, 0, -1, 1);
            rlSetMatrixProjection(proj);
            SetWindowState(FLAG_WINDOW_RESIZABLE);

            ClearBackground(WHITE);
            DrawGame();
            UpdateGame();
            
            
        EndDrawing();
    }
    QuitGame();
    return 0;
}
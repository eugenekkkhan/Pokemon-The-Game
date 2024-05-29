#ifndef PLAYER_H
#define PLAYER_H

#include "pokemon.h"
#include "raylib.h"

struct Player 
{
    float x;
    float y;
    float speed = 0.5;
    Rectangle src;
    
    void Init();
    void Update();
    void Draw();
};

#endif

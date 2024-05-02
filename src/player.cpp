#include "player.h"
#include "game.h"
#include "mathh.h"
#include "raymath.h"
#include "../assets/map.h"

const int sm = 4;
int Value = maps[0].height;

void Player::Init()
{
    x = 0;
    y = 0;

    src.height = 16;
    src.width = 16;
    src.x = 0;
    src.y = 0;
}

void Player::Update()
{
    if (map1_data[((int)(x)+480)/4+((int)(y-player.speed*2)+180)/4*map->width] != -1) 
    {
        y += player.speed*2;
    } else if(map1_data[((int)(x-player.speed*2)+480)/4+((int)(y)+180)/4*map->width] != -1)
    {
        x += player.speed*2;
    } else if(map1_data[((int)(x)+480)/4+((int)(y+player.speed*4)+180)/4*map->width] != -1)
    {
        y -= player.speed*2;
    } else if(map1_data[((int)(x+player.speed*2)+480)/4+((int)(y)+180)/4*map->width] != -1)
    {
        x -= player.speed*2;
    } else {
        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            player.speed = 0.7;
        } else {
            player.speed = 0.5;
        }
        if (IsKeyDown(KEY_A))
        {
            
            DrawText("A", 16, 100, 20*2, BLACK);
            x -= player.speed;
            src.x = 48;
        } else if (IsKeyDown(KEY_W))
        {
            DrawText("W", 16, 100, 20*2, BLACK);
            y -= player.speed;
            src.x = 16;

        } else if (IsKeyDown(KEY_S))
        {
            DrawText("S", 16, 100, 20*2, BLACK);
            y += player.speed;
            src.x = 0;
        } else if (IsKeyDown(KEY_D))
        {
            DrawText("D", 16, 100, 20*2, BLACK);
            x += player.speed;
            src.x = 32;
        }
    }

    DrawText(TextFormat("%i", ((int)x+480)/4), 16, 131, 20*2, BLACK);
    DrawText(TextFormat("%i", ((int)y+180)/4), 16, 170, 20*2, BLACK);
    DrawText(TextFormat("%i", map1_data[((int)x+480)/4+((int)y+180)/4*map->width]), 16, 201, 20*2, BLACK);
}
//296 244
//288 256

void Player::Draw()
{
    Rectangle dest;
    // dest.x = (RES_W/2-8)*sm;
    // dest.y = (RES_H/2-8)*sm;
    dest.x = x*sm-camera_x-8*sm;
    dest.y = y*sm-camera_y-8*sm;
    dest.width = 16*sm;
    dest.height = 16*sm;
    DrawTexturePro(character, src, dest, Vector2Zero(), 0, WHITE);
}

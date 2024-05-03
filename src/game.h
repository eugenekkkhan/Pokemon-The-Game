#ifndef GAME_H
#define GAME_H

#include "player.h"

#define RES_W 192*2
#define RES_H 108*2

struct Map {
    const int* tiles;
    int width;
    int height;
};

extern int camera_x;
extern int camera_y;
extern Player player;

extern Texture2D character;
extern Texture2D map_texture;
extern Music music;
extern const Map* map;

void InitGame();
void QuitGame();

void UpdateGame();
void DrawGame();

#endif
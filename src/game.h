#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <string>

#define RES_W 192*2
#define RES_H 108*2

using namespace std;

struct Map {
    const int* tiles;
    int width;
    int height;
};

extern int camera_x;
extern int camera_y;

extern int activeColorFrame;
extern int currentChoice;

extern int pokemonsPlayer1[10];

extern Player player;

extern vector <struct Pokemon> Pokemons;


extern Texture2D character;
extern Texture2D map_texture;
extern Texture2D PokemonsFront[10];


extern Texture2D enter;
extern Texture2D buttonE;
extern Texture2D buttonH;

extern Texture2D fightOverlay;
extern Texture2D helpOverlay;
extern Music music;
extern const Map* map;

extern string paths;

void InitGame();
void InitFile(vector <struct Pokemon>&);
void QuitGame();

void UpdateGame();
void DrawGame();

#endif
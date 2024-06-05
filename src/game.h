#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "pokemon.h"
#include "raylib.h"
#include <string>
#include <vector>

#define RES_W 192*2
#define RES_H 108*2

using namespace std;

struct Map 
{
    const int* tiles;
    int width;
    int height;
};

struct FightParticipant 
{
    vector <struct Pokemon> pokemonsInHand;
    vector <struct Texture> PokemonsBack;
    vector <struct Texture> PokemonsFront;
    vector <struct Sound> PokemonsSound;

    bool isFirstStep = true;

    bool whoIsActive[3] = { false, false, false };

    int SkipsLeft = 2;
};

extern bool isFight;
extern bool flagPVP;

extern int camera_x;
extern int camera_y;

extern int activeColorFrame;
extern int currentChoice;
extern bool whatPlayerChoosesPokemon;

extern int pokemonsPlayer1[10];
extern int pokemonsPlayer2[10];

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

void changePokemonInWhoIsActive(FightParticipant *P, int choice);
void changePokemon();

void DrawHealthBarsDuringTheFight();
void DrawTextWithOutline(string Text, int posX, int posY, int thickness, int fontSize, Color outlineColor, Color textColor);
void QuitGame();

void UpdateGame();
void DrawGame();

#endif
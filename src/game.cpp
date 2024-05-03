#include "raylib.h"
#include "raymath.h"
#include "mathh.h"
#include "game.h"
#include "../assets/map.h"

Texture2D map_texture;
Texture2D character;
Music music;
float timePlayed = 0.0f;

const Map* map = &maps[0];
const Map* map2 = &maps[1];
const Map* map3 = &maps[2];
const Map* map4 = &maps[3];
const Map* map5 = &maps[4];
const Map* map6 = &maps[5];
const Map* map7 = &maps[6];
const Map* map8 = &maps[7];
const Map* map9 = &maps[8];


int camera_x,
    camera_y;

float initial_x = (player.x - RES_W*3/2) - 480*4,
      initial_y = (player.y - RES_H*3/2) - 180*4;

Player player;

void InitGame()
{
    const int scaleMultiplier = 4;
    SetTargetFPS(60);

    InitWindow(RES_W*scaleMultiplier, RES_H*scaleMultiplier, "Pokemons");
    InitAudioDevice();

    Image image = LoadImage("./assets/pokemon_tileset_from_public_tiles_by_chaoticcherrycake_d5xdb0y.png");
    Image image2 = LoadImage("./assets/character.png"); 
    
    map_texture = LoadTextureFromImage(image);
    character = LoadTextureFromImage(image2);
    music = LoadMusicStream("./assets/background_music_lavender_town.mp3");

    PlayMusicStream(music);

    UnloadImage(image);
    UnloadImage(image2);


    player.Init();

}

void UpdateGame()
{
    
    player.Update();
    UpdateMusicStream(music);
    
    camera_x = (player.x - RES_W / 2)*4;
    camera_y = (player.y - RES_H / 2)*4;

}

void DrawGame()    
{
    const int scaleMultiplier = 4;
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            Rectangle dest;
            dest.height = 16*scaleMultiplier;
            dest.width = 16*scaleMultiplier;
            dest.x = (x*16 - camera_x + initial_x)*scaleMultiplier;
            dest.y = (y*16 - camera_y + initial_y)*scaleMultiplier;

            Rectangle src;

            src.height = 16;
            src.width = 16;
            
            //water
            int tile = map->tiles[x + y * map->width];
            src.x = (tile % 140) * 16;
            src.y = (tile / 140) * 16;
            DrawTexturePro(map_texture, src, dest, Vector2Zero(), 0, WHITE);

            //land
            tile = map2->tiles[x + y * map->width];
            src.x = (tile % 140) * 16;
            src.y = (tile / 140) * 16;
            DrawTexturePro(map_texture, src, dest, Vector2Zero(), 0, WHITE);

            //roads
            tile = map3->tiles[x + y * map->width];
            src.x = (tile % 140) * 16;
            src.y = (tile / 140) * 16;
            DrawTexturePro(map_texture, src, dest, Vector2Zero(), 0, WHITE);

            //trees front
            tile = map4->tiles[x + y * map->width];
            src.x = (tile % 140) * 16;
            src.y = (tile / 140) * 16;
            DrawTexturePro(map_texture, src, dest, Vector2Zero(), 0, WHITE);

            //houses front
            tile = map5->tiles[x + y * map->width];
            src.x = (tile % 140) * 16;
            src.y = (tile / 140) * 16;
            DrawTexturePro(map_texture, src, dest, Vector2Zero(), 0, WHITE);

            //lanterns, columns, bins [[and other objects
            tile = map6->tiles[x + y * map6->width];
            src.x = (tile % 140) * 16;
            src.y = (tile / 140) * 16;
            DrawTexturePro(map_texture, src, dest, Vector2Zero(), 0, WHITE);

            // SDL_RenderCopy(renderer, map_texture, &src, &dest);
        }
    }
    
    player.Draw();

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            Rectangle dest;
            dest.height = 16*scaleMultiplier;
            dest.width = 16*scaleMultiplier;
            dest.x = (x*16 - camera_x + initial_x)*scaleMultiplier;
            dest.y = (y*16 - camera_y + initial_y)*scaleMultiplier;

            Rectangle src;

            src.height = 16;
            src.width = 16;
            
            int tile = map7->tiles[x + y * map->width];
            src.x = (tile % 140) * 16;
            src.y = (tile / 140) * 16;
            DrawTexturePro(map_texture, src, dest, Vector2Zero(), 0, WHITE);

            tile = map8->tiles[x + y * map->width];
            src.x = (tile % 140) * 16;
            src.y = (tile / 140) * 16;
            DrawTexturePro(map_texture, src, dest, Vector2Zero(), 0, WHITE);

            tile = map9->tiles[x + y * map->width];
            src.x = (tile % 140) * 16;
            src.y = (tile / 140) * 16;
            DrawTexturePro(map_texture, src, dest, Vector2Zero(), 0, WHITE);
        }
    }


    // const char* text1 = (char*)camera_x;
    DrawText(TextFormat("%f", player.x), 16, 16, 20*2, BLACK);
    DrawText(TextFormat("%f", player.y), 16, 40, 20*2, BLACK);
}

void QuitGame()
{
    UnloadTexture(map_texture);
    UnloadTexture(character);
    UnloadMusicStream(music);  
    CloseAudioDevice();
    CloseWindow();
}
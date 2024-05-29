#include "raylib.h"
#include "raymath.h"
#include "mathh.h"
#include "game.h"
#include "pokemon.h"
#include "text.h"
#include "../assets/map.h"

#include <string>
#include <ctime>
#include <fstream>

using namespace std;

vector <struct Pokemon> Pokemons;

// const char* pokemons[] = {
//     "bulbasaur",
//     "caterpie",
//     "charmander",
//     "eevee",
//     "jigglypuff",
//     "pidgey",
//     "pikachu",
//     "rattata",
//     "spearow",
//     "squirtle"
// };

vector <string> Types = {
    "ELECTRIC",
    "WATER",
    "FLYING",
    "NORMAL",
    "FAIRY",
    "FIRE",
    "BUG",
    "GRASS",
};


const char* pathToPokemons = "./assets/pokemons/";

string paths = "";

Texture2D map_texture;
Texture2D character;
Texture2D opponent;
Texture2D PokemonsFront[10];
Texture2D PokemonsBack[10];
Texture2D enter;
Texture2D arrow;
Texture2D buttonE;
Texture2D buttonH;
Texture2D buttonA;
Texture2D buttonD;
Texture2D buttonW;
Texture2D buttonS;
Texture2D fightOverlay;
Texture2D helpOverlay;
Music music;
float timePlayed = 0.0f;
bool isQuest = 0;
bool isHelp = 0;
bool isFight = 0;
bool entry = 0;

int currentTile;
int currentChoice = 0;
int activeColorFrame = 0;

const Map* map = &maps[0];
const Map* map2 = &maps[1];
const Map* map3 = &maps[2];
const Map* map4 = &maps[3];
const Map* map5 = &maps[4];
const Map* map6 = &maps[5];
const Map* map7 = &maps[6];
const Map* map8 = &maps[7];
const Map* map9 = &maps[8];
const Map* map10 = &maps[9];
const Map* mapMount = &maps[10];


int camera_x,
    camera_y;

float initial_x = (player.x - RES_W*3/2) - 480*4,
      initial_y = (player.y - RES_H*3/2) - 180*4;

Player player;

int pokemonsPlayer1[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int pokemonsPlayer2[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void InitFile(vector <struct Pokemon>& PokemonsArray) {
    Pokemon currentPokemon;
    int currentType;


    ifstream in("Pokemons.txt"); 


    if (in.is_open())
    {
        // Pokemon  | Type  | HP | Atk | Def  | Sp. Atk | Sp. Def | Speed | Stamina | Stamina Atk | Stamina Sp. Atk | Regeneration | 
        // squirtle | WATER | 44 | 48  | 65   | 50      | 64      | 43    | 90      | 15          | 30              | 1/16         |
        while (in >> currentPokemon.name_pokemon >> currentPokemon.health >> currentPokemon.atk >> currentPokemon.def
        >>currentPokemon.sp_atk >> currentPokemon.sp_def >> currentPokemon.speed>>currentPokemon.stamina
        >>currentPokemon.stamina_atk_usage >> currentPokemon.stamina_sp_atk_usage >> currentPokemon.regeneration_coefficient)
        {
            in >> currentType;
            currentPokemon.type_pokemon = TypePokemon(static_cast<BasicPokemonType>(currentType));

            PokemonsArray.push_back(currentPokemon);
        }
    }
    in.close();
}

void InitGame()
{
    const int scaleMultiplier = 4;

    InitWindow(RES_W*scaleMultiplier, RES_H*scaleMultiplier, "Pokemon");
    SetTargetFPS(60);
    InitAudioDevice();
    
    Image image = LoadImage("./assets/pokemon_tileset_from_public_tiles_by_chaoticcherrycake_d5xdb0y.png");
    Image image2 = LoadImage("./assets/character.png"); 

    for (int i = 0; i < 10; i++)
    {

        Image PokemonFrontLoadImage;
        Image PokemonBackLoadImage;

        PokemonFrontLoadImage = LoadImage((pathToPokemons+string(Pokemons[i].name_pokemon)+".png").c_str());
        PokemonBackLoadImage  = LoadImage((pathToPokemons+string(Pokemons[i].name_pokemon)+"_back.png").c_str());
        
        PokemonsFront[i] = LoadTextureFromImage(PokemonFrontLoadImage);
        PokemonsBack[i] = LoadTextureFromImage(PokemonBackLoadImage);

        UnloadImage(PokemonFrontLoadImage);
        UnloadImage(PokemonBackLoadImage);

    };

    Image icon = LoadImage("./assets/button-enter.png"); 
    Image icon2 = LoadImage("./assets/button-e.png");
    Image icon3 = LoadImage("./assets/arrow.png");
    Image icon4 = LoadImage("./assets/button-h.png");
    Image icon5 = LoadImage("./assets/button-a.png");
    Image icon6 = LoadImage("./assets/button-d.png");
    Image icon7 = LoadImage("./assets/button-w.png");
    Image icon8 = LoadImage("./assets/button-s.png");
    Image fOverLay = LoadImage("./assets/fight-window.png");
    Image hOverLay = LoadImage("./assets/help-window.png");
    
    map_texture = LoadTextureFromImage(image);
    character = LoadTextureFromImage(image2);
    enter = LoadTextureFromImage(icon);
    buttonE = LoadTextureFromImage(icon2);
    buttonH = LoadTextureFromImage(icon4);
    buttonA = LoadTextureFromImage(icon5);
    buttonD = LoadTextureFromImage(icon6);
    buttonW = LoadTextureFromImage(icon7);
    buttonS = LoadTextureFromImage(icon8);

    arrow = LoadTextureFromImage(icon3);
    fightOverlay = LoadTextureFromImage(fOverLay);
    helpOverlay = LoadTextureFromImage(hOverLay);
    music = LoadMusicStream("./assets/background_music_lavender_town.mp3");

    PlayMusicStream(music);

    UnloadImage(image);
    UnloadImage(image2);
    UnloadImage(icon);
    UnloadImage(icon2);
    UnloadImage(icon3);
    UnloadImage(icon4);
    UnloadImage(fOverLay);
    UnloadImage(hOverLay);


    player.Init();

}

void UpdateGame()
{
    if (!isQuest)
    {
        player.Update();
        
        camera_x = (player.x - RES_W / 2)*4;
        camera_y = (player.y - RES_H / 2)*4;
    }
    UpdateMusicStream(music);

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

            //mountain
            tile = mapMount->tiles[x + y * map->width];
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

            //lanterns, columns, bins and other objects front
            tile = map6->tiles[x + y * map6->width];
            src.x = (tile % 140) * 16;
            src.y = (tile / 140) * 16;
            DrawTexturePro(map_texture, src, dest, Vector2Zero(), 0, WHITE);

            // quests
            tile = map10->tiles[x+y*map10->width];
            src.x = (tile % 140) * 16;
            src.y = (tile / 140) * 16;
            DrawTexturePro(map_texture, src, dest, Vector2Zero(), 0, WHITE);
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

    currentTile = map_quests[((int)(player.x)+480)/4+((int)(player.y-player.speed)+180)/4*map->width];

    if (currentTile != -1)
    {
        if (!isQuest)
        {
            DrawText("Enter", (RES_W-48)*4, (RES_H-20)*4, 20*2, BLACK);
            DrawTexture(enter, (RES_W-18)*4, (RES_H-20)*4, WHITE);

            for (int i = 0; i < 10; i++)
            {
                pokemonsPlayer1[i] = 0;
                pokemonsPlayer2[i] = 0;
            }
            entry = 0;
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            isQuest = 1;
            
        }


    }

    if (IsKeyPressed(KEY_E))
    {
        isQuest = 0;
    }

    if (isQuest)
    {
        int enemyIndex = 6;
        bool flagPVP = true;

        if (currentTile == 19741 || currentTile == 19741+140)
        {
           enemyIndex = 4;
           flagPVP = false;
        }
        if (currentTile == 19745 || currentTile == 19745+140)
        {
           enemyIndex = 3; 
           flagPVP = false;
        }
        if (currentTile == 19749 || currentTile == 19749+140)
        {
           enemyIndex = 2; 
           flagPVP = false;
        }
        if (currentTile == 19753 || currentTile == 19753+140)
        {
           enemyIndex = 1;
           flagPVP = false;
        }
        if (currentTile == 19757 || currentTile == 19757+140)
        {
           enemyIndex = 5;
           flagPVP = false; 
        }
        if (currentTile == 20021 || currentTile == 20021+140)
        {
           enemyIndex = 6;
           flagPVP = false; 
        }
        if (currentTile == 20025 || currentTile == 20025+140)
        {
           enemyIndex = 8; 
           flagPVP = false;
        }
        if (currentTile == 20029 || currentTile == 20029+140)
        {
           enemyIndex = 0;
           flagPVP = false; 
        }
        if (currentTile == 20033 || currentTile == 20033+140)
        {
           enemyIndex = 7; 
           flagPVP = false;
        }
        if (currentTile == 20037 || currentTile == 20037+140)
        {
           enemyIndex = 9;
           flagPVP = false;
        }

        int FightOverlayWindowHeight = 800;
        int FightOverlayWindowWidth = 600;

        DrawTexture(fightOverlay, (RES_W/2)*4-FightOverlayWindowWidth/2, (RES_H/2)*4-FightOverlayWindowHeight/2, WHITE);

        if (!flagPVP)
        {
            string FightWith = "Fight with " + Pokemons[enemyIndex].name_pokemon+"!";
            DrawText(FightWith.c_str(), (RES_W/2-70)*4, (RES_H/2-96)*4, 20*2, BLACK);

            DrawTexture(enter, (RES_W-18)*4, (RES_H-50)*4, WHITE);
            DrawText("Fight!", (RES_W-48)*4, (RES_H-50)*4, 20*2, BLACK);

        } else
        {
            DrawText("PVP fight!", (RES_W/2-70)*4, (RES_H/2-96)*4, 20*2, BLACK);

            DrawTexture(enter, (RES_W-18)*4, (RES_H-50)*4, WHITE);
            DrawText("Choose", (RES_W-57)*4, (RES_H-50)*4, 20*2, BLACK);
        
        }

        DrawTexture(buttonE, (RES_W-18)*4, (RES_H-20)*4, WHITE);
        DrawText("Exit", (RES_W-40)*4, (RES_H-20)*4, 20*2, BLACK);

        DrawTexture(buttonW, 12*4, (RES_H-35)*4, WHITE);
        DrawText("Go up", 23*4, (RES_H-35)*4, 20*2, BLACK);

        DrawTexture(buttonS, 12*4, (RES_H-20)*4, WHITE);
        DrawText("Go down", 23*4, (RES_H-20)*4, 20*2, BLACK);

        if (!isHelp)
        {

            DrawTexture(buttonH, (RES_W-18)*4, (RES_H-35)*4, WHITE);
            DrawText("Help", (RES_W-42)*4, (RES_H-35)*4, 20*2, BLACK);

        } else
        {
            HelpWindow();
        }

        if (IsKeyPressed(KEY_H))
        {
            isHelp = !isHelp;
        }

        
        if (IsKeyPressed(KEY_W)) 
        {
            currentChoice--;
            if (currentChoice < 0)
            {
                currentChoice = 9;
            }
        }
        if (IsKeyPressed(KEY_S)) 
        {
            currentChoice++;
            if (currentChoice > 9)
            {
                currentChoice = 0;
            }
        }

        DrawTexturePro(PokemonsFront[enemyIndex], { 0.0f, 0.0f, 96.0f, 96.0f }, { (RES_W/2-20)*4.0f, (RES_H/2-90)*4.0f, 96*4.0f, 96*4.0f }, Vector2Zero(), 0, WHITE);
        DrawTexturePro(PokemonsBack[currentChoice], { 0.0f, 0.0f, 96.0f, 96.0f }, { (RES_W/2-80)*4.0f, (RES_H/2-50)*4.0f, 96*4.0f, 96*4.0f }, Vector2Zero(), 0, WHITE);

        if (!flagPVP)
        {
            DrawText("Choose your pokemon:", (RES_W/2)*4-285, (RES_H/2)*4+280-42, 10*2, BLACK);
        } else
        {
            int cnt = 0;
            for (int i = 0; i < 10; i++)
            {
                if (pokemonsPlayer1[i])
                {
                    cnt++;
                }
            }


            string ChooseYourPokemon = "Choose your pokemons("+ to_string(cnt)+"/3)!";
            DrawText(ChooseYourPokemon.c_str(), (RES_W/2)*4-285, (RES_H/2)*4+280-42, 10*2, BLACK);


            if (IsKeyPressed(KEY_ENTER) && entry)
            {
                pokemonsPlayer1[(currentChoice)%10] = !pokemonsPlayer1[(currentChoice)%10];

                if (pokemonsPlayer1[(currentChoice)%10])
                {
                    cnt++;
                }

                if (cnt>3)
                {
                    pokemonsPlayer1[(currentChoice)%10] = 0;
                }

            }
            entry = true;

            if (cnt==3)
            {
                DrawTexture(buttonD, 12*4, (RES_H-50)*4, WHITE);
                DrawText("Next player", 23*4, (RES_H-50)*4, 20*2, BLACK);

                DrawTexture(buttonS, 12*4, (RES_H-20)*4, WHITE);
                DrawText("Go down", 23*4, (RES_H-20)*4, 20*2, BLACK);

            }
            
        }


        activeColorFrame++; // для изменения покраски активной строки с выбором

        if (!isFight)
        {
            ColNames();

            ListOfPokemons();
        } else 
        {
            
        }
        
    }


    // DrawText((paths).c_str(), 0, RES_H+100, 10*2, BLACK);   
    
    // const char* text1 = (char*)camera_x;
    // DrawText(TextFormat("%f", player.x), 16, 16, 20*2, BLACK);
    // DrawText(TextFormat("%f", player.y), 16, 40, 20*2, BLACK);
}


void QuitGame()
{
    UnloadTexture(map_texture);
    UnloadTexture(character);
    UnloadTexture(opponent);
    for (int i = 0; i<10; i++)
    {
        UnloadTexture(PokemonsFront[i]);
        UnloadTexture(PokemonsBack[i]);
    }
    UnloadTexture(enter);
    UnloadTexture(arrow);
    UnloadTexture(buttonE);
    UnloadTexture(buttonH);
    UnloadTexture(buttonA);
    UnloadTexture(buttonD);
    UnloadTexture(buttonW);
    UnloadTexture(buttonS);
    UnloadTexture(fightOverlay);
    UnloadTexture(helpOverlay);
    UnloadMusicStream(music); 
    CloseAudioDevice();
    CloseWindow();
}
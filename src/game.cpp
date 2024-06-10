#include "raylib.h"
#include "raymath.h"
#include "game.h"
#include "pokemon.h"
#include "text.h"
#include "../assets/map.h"

#include <string>
#include <ctime>
#include <fstream>

using namespace std;

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

float MatrixPokemons[8][8] = {
    { 0.5f,  1.0f,   0.5f,   1.0f,   1.0f,   1.0f,   1.0f,  1.0f  },
    { 2.0f,  0.5f,   1.0f,   1.0f,   1.0f,   0.5f,   1.0f,  2.0f  }, 
    { 2.0f,  1.0f,   1.0f,   1.0f,   1.0f,   1.0f,   0.5f,  0.5f  },
    { 1.0f,  1.0f,   1.0f,   1.0f,   1.0f,   1.0f,   1.0f,  1.0f  },
    { 1.0f,  1.0f,   1.0f,   1.0f,   1.0f,   1.0f,   0.5f,  2.0f  }, 
    { 1.0f,  2.0f,   1.0f,   1.0f,   0.5f,   0.5f,   0.5f,  0.5f  },
    { 1.0f,  1.0f,   2.0f,   1.0f,   1.0f,   2.0f,   1.0f,  0.5f  },
    { 0.5f,  0.5f,   2.0f,   1.0f,   0.5f,   2.0f,   1.0f,  0.25f }
};

int camera_x,
    camera_y;

float initial_x = (player.x - RES_W*3/2) - 480*4,
      initial_y = (player.y - RES_H*3/2) - 180*4;

Player player;

int pokemonsPlayer1[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int pokemonsPlayer2[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void InitFile(vector <struct Pokemon>& PokemonsArray) {
    int currentType;


    ifstream in("Pokemons.txt"); 


    if (in.is_open())
    {
        // Pokemon  | HP | Atk | Def  | Sp. Atk | Sp. Def | Speed | Stamina | Stamina Atk | Stamina Sp. Atk | Regeneration |  Type   |
        // squirtle | 44 | 48  | 65   | 50      | 64      | 43    | 90      | 15          | 30              | 1/16         |  WATER  |
        string name;
        int health;
        int atk;
        int def;
        int sp_atk;
        int sp_def;
        int speed;
        int stamina;
        int stamina_atk_usage;
        int stamina_sp_atk_usage;
        float regeneration_coefficient;
        while (in >> name >> health >> atk >> def
        >> sp_atk >> sp_def >> speed >> stamina
        >> stamina_atk_usage >> stamina_sp_atk_usage >> regeneration_coefficient >> currentType)
        {
            Pokemon pokemon(name, health, atk, def, sp_atk, sp_def, speed, stamina,
            stamina_atk_usage, stamina_sp_atk_usage, regeneration_coefficient, TypePokemon((BasicPokemonType)currentType));

            PokemonsArray.push_back(pokemon);
        }
    }
    in.close();
}

void InitGame()
{
    const int scaleMultiplier = 4;

    InitWindow(RES_W*scaleMultiplier, RES_H*scaleMultiplier, "Pokemon");
    // SetTargetFPS(60);
    SetWindowState(FLAG_VSYNC_HINT);
    InitAudioDevice();


    for (int i = 0; i < 10; i++)
    {
        
        PokemonsFront[i] = LoadTexture((pathToPokemons+string(Pokemons[i].name_pokemon)+".png").c_str());
        PokemonsBack[i] = LoadTexture((pathToPokemons+string(Pokemons[i].name_pokemon)+"_back.png").c_str());

        PokemonsSound.push_back(LoadSound((pathToPokemonsSounds+string(Pokemons[i].name_pokemon)+".mp3").c_str()));

    };
    
    map_texture = LoadTexture("./assets/pokemon_tileset_from_public_tiles_by_chaoticcherrycake_d5xdb0y.png");
    character = LoadTexture("./assets/character.png");
    enter = LoadTexture("./assets/button-enter.png");
    arrow = LoadTexture("./assets/arrow.png");

    buttonE = LoadTexture("./assets/button-e.png");
    buttonF = LoadTexture("./assets/button-f.png");
    buttonH = LoadTexture("./assets/button-h.png");
    buttonA = LoadTexture("./assets/button-a.png");
    buttonD = LoadTexture("./assets/button-d.png");
    buttonW = LoadTexture("./assets/button-w.png");
    buttonS = LoadTexture("./assets/button-s.png");

    healthBar =            LoadTexture("./assets/health-bar.png");
    healthBarEnemy =       LoadTexture("./assets/health-bar-enemy.png");
    healthBarActive =      LoadTexture("./assets/health-bar-active.png");
    healthBarEnemyActive = LoadTexture("./assets/health-bar-enemy-active.png");
    deadSkull = LoadTexture("./assets/deadskull.png");

    fightOverlay = LoadTexture("./assets/fight-window.png");
    helpOverlay = LoadTexture("./assets/help-window.png");
    music = LoadMusicStream("./assets/background_music_lavender_town.mp3");

    PlayMusicStream(music);
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
        isFight = 0;
        isInitFirstStep = 1;
        isChangingPokemon = 0;
        entry2 = false;
        whoGoes = false;
        initPokemons = 0;
    
        whatPlayerChoosesPokemon = 0;
        actionChoice = 0;
        currentChoice = 0;
        currentChangeChoice = 0;
        
        for (int i = 0; i < 3; i++)
        {
            Player1.whoIsActive[i] = false;
            Player2.whoIsActive[i] = false;
        }
        Player1.pokemonsInHand.clear();
        Player1.PokemonsFront.clear();
        Player1.PokemonsBack.clear();
        Player1.PokemonsSound.clear();
        Player1.isFirstStep = 1;
        Player1.SkipsLeft = 2;

        Player2.pokemonsInHand.clear();
        Player2.PokemonsFront.clear();
        Player2.PokemonsBack.clear();
        Player2.PokemonsSound.clear();
        Player2.isFirstStep = 1;
        Player2.SkipsLeft = 2;
    }

    if (isQuest)
    {
        int enemyIndex = 6;
        
        flagPVP = true;

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

            if (!isFight)
            {
                DrawTexture(buttonF, (RES_W-18)*4, (RES_H-50)*4, WHITE);
                DrawText("Fight!", (RES_W-48)*4, (RES_H-50)*4, 20*2, BLACK);
            } else
            {
                DrawTexture(enter, (RES_W-18)*4, (RES_H-50)*4, WHITE);
                DrawText("Choose", (RES_W-57)*4, (RES_H-50)*4, 20*2, BLACK);
            }

            if (IsKeyPressed(KEY_F)) 
            {
                isFight = 1;
            }

        } else
        {
            int cnt = 0;
            for (int i = 0; i < 10; i++)
            {
                if (pokemonsPlayer1[i])
                {
                    cnt++;
                }
                if (pokemonsPlayer2[i])
                {
                    cnt++;
                }
             }
    
            if (cnt == 6 && !isFight)
            {
                DrawTexture(buttonF, (RES_W-18)*4, (RES_H-65)*4, WHITE);
                DrawText("Fight!", (RES_W-48)*4, (RES_H-65)*4, 20*2, BLACK);
                if (IsKeyPressed(KEY_F)) 
                {
                    isFight = 1;
                }
            }

            DrawTexture(enter, (RES_W-18)*4, (RES_H-50)*4, WHITE);
            DrawText("Choose", (RES_W-57)*4, (RES_H-50)*4, 20*2, BLACK);
        
        }

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

        DrawTexture(buttonE, (RES_W-18)*4, (RES_H-20)*4, WHITE);
        DrawText("Exit", (RES_W-40)*4, (RES_H-20)*4, 20*2, BLACK);

        DrawTexture(buttonW, 12*4, (RES_H-35)*4, WHITE);
        DrawText("Go up", 23*4, (RES_H-35)*4, 20*2, BLACK);

        DrawTexture(buttonS, 12*4, (RES_H-20)*4, WHITE);
        DrawText("Go down", 23*4, (RES_H-20)*4, 20*2, BLACK);

        if (!isFight)
        {
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
        if (!flagPVP)
        {
            DrawText("Choose your pokemon:", (RES_W/2)*4-285, (RES_H/2)*4+280-42, 10*2, BLACK);
        } else
        {
            int cnt = 0;
            if (!whatPlayerChoosesPokemon)
            {
                for (int i = 0; i < 10; i++)
                {
                    if (pokemonsPlayer1[i])
                    {
                        cnt++;
                    }
                }
            } else
            {
                for (int i = 0; i < 10; i++)
                {
                    if (pokemonsPlayer2[i])
                    {
                        cnt++;
                    }
                }  
            }


            string ChooseYourPokemon = "Choose your pokemons("+ to_string(cnt)+"/3)!";
            DrawText(ChooseYourPokemon.c_str(), (RES_W/2)*4-285, (RES_H/2)*4+280-42, 10*2, BLACK);

            if (IsKeyPressed(KEY_ENTER) && entry)
            {
                if (!whatPlayerChoosesPokemon)
                {
                    if (!pokemonsPlayer2[(currentChoice)%10])
                    {
                        pokemonsPlayer1[(currentChoice)%10] = !pokemonsPlayer1[(currentChoice)%10];
                        if (pokemonsPlayer1[(currentChoice)%10])
                        {
                            PlaySound(PokemonsSound[currentChoice]);
                        }
                    }
                    if (pokemonsPlayer1[(currentChoice)%10])
                    {
                        cnt++;
                    }

                    if (cnt>3)
                    {
                        pokemonsPlayer1[(currentChoice)%10] = 0;
                    }
                } else
                {
                    if (!pokemonsPlayer1[(currentChoice)%10])
                    {
                        pokemonsPlayer2[(currentChoice)%10] = !pokemonsPlayer2[(currentChoice)%10];
                        if (pokemonsPlayer2[(currentChoice)%10])
                        {
                            PlaySound(PokemonsSound[currentChoice]);
                        }
                    }

                    if (pokemonsPlayer2[(currentChoice)%10])
                    {
                        cnt++;
                    }

                    if (cnt>3)
                    {
                        pokemonsPlayer2[(currentChoice)%10] = 0;
                    }
                }

            }
            entry = true;
        }

        int rowCounter = 0;
        int rowHeight = 90;
        // drawing preview health bar for the first player
        for (int i = 0; i < 10; i++)
        {
            if (pokemonsPlayer1[i] != 0)
            {
                Rectangle src;
                src.height = 43.0f;
                src.width = 148.0f;
                src.x = 0.0f;
                src.y = 0.0f;

                Rectangle dest;
                dest.height = 43*2.0f;
                dest.width = 148*2.0f;
                dest.x = (RES_W/2)*4.0f;
                dest.y = (RES_H/2)*4.0f-60+rowHeight*rowCounter;   

                string currentType;
                Color currentColorOfType;
                switch (Pokemons[i].type_pokemon.type_pokemon)
                {
                    case BasicPokemonType::ELECTRIC:
                        currentType = "ELECTRIC";
                        currentColorOfType = YELLOW;
                        break;
                    case BasicPokemonType::WATER:
                        currentType = "WATER";
                        currentColorOfType = Color{ 45, 164, 255, 255 };
                        break;
                    case BasicPokemonType::FLYING:
                        currentType = "FLYING";
                        currentColorOfType = PURPLE;
                        break;
                    case BasicPokemonType::FAIRY:
                        currentType = "FAIRY";
                        currentColorOfType = PINK;
                        break;
                    case BasicPokemonType::FIRE:
                        currentType = "FIRE";
                        currentColorOfType = ORANGE;
                        break;
                    case BasicPokemonType::BUG:
                        currentType = "BUG";
                        currentColorOfType = Color{ 45, 255, 237, 255 };
                        break;
                    case BasicPokemonType::GRASS:
                        currentType = "GRASS";
                        currentColorOfType = Color{ 65, 255, 45, 255 };
                        break;
                    default:
                        currentType = "NORMAL";
                        currentColorOfType = WHITE;
                        break;
                }              

                DrawTexturePro(healthBar, src, dest, Vector2Zero(), 0, WHITE);
                DrawText(Pokemons[i].name_pokemon.c_str(), (RES_W/2)*4.0f+56, (RES_H/2)*4.0f-42+rowHeight*rowCounter, 10*2, Color{ 228, 240, 240, 255});

                DrawRectangle((RES_W/2)*4.0f+280-currentType.length()*14, (RES_H/2)*4.0f-42+rowHeight*rowCounter, currentType.length()*14+4, 18, BLACK);
                DrawText(currentType.c_str(), (RES_W/2)*4.0f+282-currentType.length()*14, (RES_H/2)*4.0f-42+rowHeight*rowCounter, 10*2, currentColorOfType);
                
                DrawRectangle(dest.x+44, dest.y+78, 121*Pokemons[i].stamina/Pokemons[i].max_stamina*2, 2, Color{ 0, 220, 220, 255 });
                DrawRectangle(dest.x+44, dest.y+78+2, 121*Pokemons[i].stamina/Pokemons[i].max_stamina*2, 2, Color{ 0, 180, 180, 255 });
                
                //shadow
                DrawText(TextFormat("%i", Pokemons[i].stamina), dest.x+157, dest.y+60, 8*2, BLACK);
                DrawText(TextFormat("%i", Pokemons[i].max_stamina), dest.x+157+34, dest.y+60, 8*2, BLACK);

                DrawText(TextFormat("%i", Pokemons[i].stamina), dest.x+156, dest.y+59, 8*2, Color{ 0, 220, 220, 255 });
                DrawText(TextFormat("%i", Pokemons[i].max_stamina), dest.x+156+34, dest.y+59, 8*2, Color{ 0, 220, 220, 255 });

                DrawRectangle(dest.x+140, dest.y+48, 73*Pokemons[i].health/Pokemons[i].max_health*2, 2, Color{ 255, 96, 98, 255 });
                DrawRectangle(dest.x+140, dest.y+48+2, 73*Pokemons[i].stamina/Pokemons[i].max_stamina*2, 2, Color{ 231, 68, 70, 255 });

                //shadow
                DrawText(TextFormat("%i", Pokemons[i].health), dest.x+225, dest.y+60, 8*2, BLACK);
                DrawText(TextFormat("%i", Pokemons[i].max_health), dest.x+225+34, dest.y+60, 8*2, BLACK);

                DrawText(TextFormat("%i", Pokemons[i].health), dest.x+224, dest.y+59, 8*2, Color{ 255, 96, 98, 255 });
                DrawText(TextFormat("%i", Pokemons[i].max_health), dest.x+224+34, dest.y+59, 8*2, Color{ 255, 96, 98, 255 });

                rowCounter++;
            }
        }
        rowCounter = 0;
        // drawing preview health bar for the second player
        for (int i = 0; i < 10; i++)
        {
            if (pokemonsPlayer2[i] != 0)
            {
                string currentType;
                Color currentColorOfType;
                switch (Pokemons[i].type_pokemon.type_pokemon)
                {
                    case BasicPokemonType::ELECTRIC:
                        currentType = "ELECTRIC";
                        currentColorOfType = YELLOW;
                        break;
                    case BasicPokemonType::WATER:
                        currentType = "WATER";
                        currentColorOfType = Color{ 45, 164, 255, 255 };
                        break;
                    case BasicPokemonType::FLYING:
                        currentType = "FLYING";
                        currentColorOfType = PURPLE;
                        break;
                    case BasicPokemonType::FAIRY:
                        currentType = "FAIRY";
                        currentColorOfType = PINK;
                        break;
                    case BasicPokemonType::FIRE:
                        currentType = "FIRE";
                        currentColorOfType = ORANGE;
                        break;
                    case BasicPokemonType::BUG:
                        currentType = "BUG";
                        currentColorOfType = Color{ 45, 255, 237, 255 };
                        break;
                    case BasicPokemonType::GRASS:
                        currentType = "GRASS";
                        currentColorOfType = Color{ 65, 255, 45, 255 };
                        break;
                    default:
                        currentType = "NORMAL";
                        currentColorOfType = WHITE;
                        break;
                } 

                Rectangle src;
                src.height = 43.0f;
                src.width = 148.0f;
                src.x = 0.0f;
                src.y = 0.0f;

                Rectangle dest;
                dest.height = 43*2.0f;
                dest.width = 148*2.0f;
                dest.x = (RES_W/2)*4.0f-296;
                dest.y = (RES_H/2)*4.0f-376+rowHeight*rowCounter;              

                DrawTexturePro(healthBarEnemy, src, dest, Vector2Zero(), 0, WHITE);
                DrawText(Pokemons[i].name_pokemon.c_str(), dest.x+12, dest.y+16, 10*2, Color{ 228, 240, 240, 255 });

                DrawRectangle(dest.x+250-currentType.length()*14, dest.y+14, currentType.length()*14+4, 18, BLACK);
                DrawText(currentType.c_str(), (RES_W/2)*4.0f-44-currentType.length()*14, dest.y+14, 10*2, currentColorOfType);

                DrawRectangle(dest.x+14, dest.y+78, 121*Pokemons[i].stamina/Pokemons[i].max_stamina*2, 2, Color{ 0, 220, 220, 255 });
                DrawRectangle(dest.x+14, dest.y+78+2, 121*Pokemons[i].stamina/Pokemons[i].max_stamina*2, 2, Color{ 0, 180, 180, 255 });

                //shadow
                DrawText(TextFormat("%i", Pokemons[i].stamina), dest.x+25, dest.y+60, 8*2, BLACK);
                DrawText(TextFormat("%i", Pokemons[i].max_stamina), dest.x+59, dest.y+60, 8*2, BLACK);

                DrawText(TextFormat("%i", Pokemons[i].stamina), dest.x+24, dest.y+59, 8*2, Color{ 0, 220, 220, 255 });
                DrawText(TextFormat("%i", Pokemons[i].max_stamina), dest.x+58, dest.y+59, 8*2, Color{ 0, 220, 220, 255 });

                DrawRectangle(dest.x+14, dest.y+48, 73*Pokemons[i].health/Pokemons[i].max_health*2, 2, Color{ 255, 96, 98, 255 });
                DrawRectangle(dest.x+14, dest.y+48+2, 73*Pokemons[i].stamina/Pokemons[i].max_stamina*2, 2, Color{ 231, 68, 70, 255 });

                //shadow
                DrawText(TextFormat("%i", Pokemons[i].health), dest.x+93, dest.y+60, 8*2, BLACK);
                DrawText(TextFormat("%i", Pokemons[i].max_health), dest.x+93+34, dest.y+60, 8*2, BLACK);

                DrawText(TextFormat("%i", Pokemons[i].health), dest.x+92, dest.y+59, 8*2, Color{ 255, 96, 98, 255 });
                DrawText(TextFormat("%i", Pokemons[i].max_health), dest.x+92+34, dest.y+59, 8*2, Color{ 255, 96, 98, 255 });
                rowCounter++;
            }
        }

        if (flagPVP) {
            if (!whatPlayerChoosesPokemon)
            {
                DrawTexture(buttonD, 12*4, (RES_H-50)*4, WHITE);
                DrawText("Next player", 23*4, (RES_H-50)*4, 20*2, BLACK);
            } else
            {
                DrawTexture(buttonA, 12*4, (RES_H-50)*4, WHITE);
                DrawText("Prev. player", 23*4, (RES_H-50)*4, 20*2, BLACK);
            }
    
            if (IsKeyPressed(KEY_D))
            {
                whatPlayerChoosesPokemon = 1;
            }
            if (IsKeyPressed(KEY_A))
        {
            whatPlayerChoosesPokemon = 0;
        }
        }
        activeColorFrame++; // для изменения покраски активной строки с выбором

        DrawText("?", (RES_W/2+20)*4.0f, (RES_H/2-110+57)*4.0f, 40*4.0f, GRAY);
        DrawText("?", (RES_W/2-44)*4.0f, (RES_H/2-70+57)*4.0f, 40*4.0f, GRAY);

        ColNames();

        ListOfPokemons();
        } else if (flagPVP)
        {
            // * There PVP Fight starts
            for (int i = 0; i < 10; i++)
            {
                if (pokemonsPlayer1[i]!=0)
                {
                    Player1.pokemonsInHand.push_back(Pokemons[i]);
                    Player1.PokemonsFront.push_back(PokemonsFront[i]);
                    Player1.PokemonsBack.push_back(PokemonsBack[i]);
                    Player1.PokemonsSound.push_back(PokemonsSound[i]);
                }
                if (pokemonsPlayer2[i]!=0)
                {
                    Player2.pokemonsInHand.push_back(Pokemons[i]);
                    Player2.PokemonsFront.push_back(PokemonsFront[i]);
                    Player2.PokemonsBack.push_back(PokemonsBack[i]);
                    Player2.PokemonsSound.push_back(PokemonsSound[i]);
                }
            }

            if (isInitFirstStep)
            {
                int maxSpeed1 = 0;
                int maxSpeed2 = 0;
                int fastestPokemonIndex1 = 0;
                int fastestPokemonIndex2 = 0;

                for (int i = 0; i < 3; i++)
                {
                    if (Player1.pokemonsInHand[i].speed > maxSpeed1)
                    {
                        maxSpeed1 = Player1.pokemonsInHand[i].speed;
                        fastestPokemonIndex1 = i;
                    }
                    if (Player2.pokemonsInHand[i].speed > maxSpeed2)
                    {
                        maxSpeed2 = Player2.pokemonsInHand[i].speed;
                        fastestPokemonIndex2 = i;
                    }
                }
                currentPokemonIndex1 = fastestPokemonIndex1;
                currentPokemonIndex2 = fastestPokemonIndex2;

                Player1.whoIsActive[currentPokemonIndex1] = true;
                Player2.whoIsActive[currentPokemonIndex2] = true;
                if (Player2.pokemonsInHand[currentPokemonIndex1].speed > Player1.pokemonsInHand[currentPokemonIndex1].speed)
                {
                    whoGoes = true;
                } else
                {
                    whoGoes = false;
                }

                
            }

            vector <string> actions = {
                "Attack",
                "Special attack",
                "Regeneration",
                "Skip a turn",
                "Change pokemon"
            };

            activeColorFrame++; // для изменения покраски активной строки с выбором

            if (!whoGoes)
            {
                currentPlayer = &Player1;
                enemyOfCurrentPlayer = &Player2;
                currentPokemonIndex = &currentPokemonIndex1;
                enemyOfCurrentPokemonIndex = &currentPokemonIndex2;
            } else
            {
                currentPlayer = &Player2;
                enemyOfCurrentPlayer = &Player1;
                currentPokemonIndex = &currentPokemonIndex2;
                enemyOfCurrentPokemonIndex = &currentPokemonIndex1;
            }

            if (!isChangingPokemon)    
            {
                if (IsKeyPressed(KEY_W))
                {
                    actionChoice--;
                    if (actionChoice < 0)
                    {
                        actionChoice = 4;
                    }

                    if (currentPlayer->isFirstStep && actionChoice == 4)
                    {
                        actionChoice--;
                    }
                }
                if (IsKeyPressed(KEY_S))
                {
                    actionChoice++;
                    if (actionChoice > 4)
                    {
                        actionChoice = 0;
                    }

                    if (currentPlayer->isFirstStep && actionChoice >= 4)
                    {
                        actionChoice = 0;
                    }
                }
            } else
            {
                if (IsKeyPressed(KEY_W))
                {
                    currentChangeChoice--;


                    if (currentChangeChoice<0)
                    {
                        currentChangeChoice = 2;
                    }

                    if (currentPlayer->pokemonsInHand[currentChangeChoice].live == 0)
                    {
                        currentChangeChoice--;
                        if (currentChangeChoice<0)
                        {
                            currentChangeChoice = 2;
                            
                        }

                    }
                }
                if (IsKeyPressed(KEY_S))
                {
                    currentChangeChoice++;

                    
                    if (currentChangeChoice>2)
                    {
                        currentChangeChoice = 0;
                        
                    }

                    if (currentPlayer->pokemonsInHand[currentChangeChoice].live == 0)
                    {
                        currentChangeChoice++;
                        if (currentChangeChoice>2)
                        {
                            currentChangeChoice = 0;
                            
                        }
                    }
                }
                    
            }

            DrawText("Choose action:", (RES_W/2)*4-285, (RES_H/2)*4+280-42, 10*2, BLACK);
            float Multiplier = MatrixPokemons[(int)currentPlayer->pokemonsInHand[*currentPokemonIndex].type_pokemon.type_pokemon][(int)enemyOfCurrentPlayer->pokemonsInHand[*enemyOfCurrentPokemonIndex].type_pokemon.type_pokemon];
            int whatDamageCommonAttack = currentPlayer->pokemonsInHand[*currentPokemonIndex].atk-(int)(enemyOfCurrentPlayer->pokemonsInHand[*enemyOfCurrentPokemonIndex].def*Multiplier);
            whatDamageCommonAttack = (whatDamageCommonAttack > 0) ? whatDamageCommonAttack : 0;

            int whatDamageSpecialAttack = currentPlayer->pokemonsInHand[*currentPokemonIndex].sp_atk-(int)(enemyOfCurrentPlayer->pokemonsInHand[*enemyOfCurrentPokemonIndex].sp_def*Multiplier);
            whatDamageSpecialAttack = (whatDamageSpecialAttack > 0) ? whatDamageSpecialAttack : 0;

            int staminaCommonAttackUsage = currentPlayer->pokemonsInHand[*currentPokemonIndex].stamina_atk_usage;
            int staminaSpecialAttackUsage = currentPlayer->pokemonsInHand[*currentPokemonIndex].stamina_sp_atk_usage;
            
            
            DrawText("HP (damage)", (RES_W/2)*4-100, (RES_H/2)*4+280-42, 10*2, Color{ 153, 0, 0, 255 });

            DrawText("Stamina usage", (RES_W/2)*4+30, (RES_H/2)*4+280-42, 10*2, Color{ 0, 102, 102, 255 });
            for (int i = 0; i < actions.size(); i++)
            {
                if (i == 0)
                {
                    DrawText((to_string(i+1)+". "+actions[i]).c_str(), (RES_W/2)*4-285, (RES_H/2)*4+280-21+18*i, 10*2, ((activeColorFrame/10)%2 && i == actionChoice) ? YELLOW : BLACK);
                    
                    // how many damage gets enemy after common attack
                    DrawText(TextFormat("%i", whatDamageCommonAttack), (RES_W/2)*4-50, (RES_H/2)*4+280-21+18*i, 10*2, ((activeColorFrame/10)%2 && i == actionChoice) ? YELLOW : Color{ 153, 0, 0, 255 });


                    DrawText(TextFormat("%i", staminaCommonAttackUsage), (RES_W/2)*4+80, (RES_H/2)*4+280-21+18*i, 10*2, ((activeColorFrame/10)%2 && i == actionChoice) ? YELLOW : Color{ 0, 102, 102, 255 });
                } else if (i == 1)
                {
                    DrawText((to_string(i+1)+". "+actions[i]).c_str(), (RES_W/2)*4-285, (RES_H/2)*4+280-21+18*i, 10*2, ((activeColorFrame/10)%2 && i == actionChoice) ? YELLOW : BLACK);
                    
                    // how many damage gets enemy after special attack
                    DrawText(TextFormat("%i", whatDamageSpecialAttack), (RES_W/2)*4-50, (RES_H/2)*4+280-21+18*i, 10*2, ((activeColorFrame/10)%2 && i == actionChoice) ? YELLOW : Color{ 153, 0, 0, 255 });


                    DrawText(TextFormat("%i", staminaSpecialAttackUsage), (RES_W/2)*4+80, (RES_H/2)*4+280-21+18*i, 10*2, ((activeColorFrame/10)%2 && i == actionChoice) ? YELLOW : Color{ 0, 102, 102, 255 });
                } else if (i == 2)
                {
                    DrawText((to_string(i+1)+". "+actions[i]+" (left: "+to_string(currentPlayer->pokemonsInHand[*currentPokemonIndex].regen_left)+"/1, ret. "+ TextFormat("%0.0lf", (float)(currentPlayer->pokemonsInHand[*currentPokemonIndex].regeneration_coefficient*100))+"% from max health)").c_str(), (RES_W/2)*4-285, (RES_H/2)*4+280-21+18*i, 10*2, ((activeColorFrame/10)%2 && i == actionChoice) ? YELLOW : BLACK); 
                } else if (i == 3)
                {
                    DrawText((to_string(i+1)+". "+actions[i]+" (Skips left:"+to_string(currentPlayer->SkipsLeft)+"/2)").c_str(), (RES_W/2)*4-285, (RES_H/2)*4+280-21+18*i, 10*2, ((activeColorFrame/10)%2 && i == actionChoice) ? YELLOW : BLACK);
                }
                if (i == 4 && !currentPlayer->isFirstStep)
                {
                    DrawText((to_string(i+1)+". "+actions[i]).c_str(), (RES_W/2)*4-285, (RES_H/2)*4+280-21+18*i, 10*2, ((activeColorFrame/10)%2 && i == actionChoice) ? YELLOW : BLACK);
                }
            }
            
            if (currentPlayer->pokemonsInHand[*currentPokemonIndex].live == 0)
            {
                actionChoice = 4;
            }
            if ((!Player1.pokemonsInHand[0].live && !Player1.pokemonsInHand[1].live && !Player1.pokemonsInHand[2].live || !Player1.SkipsLeft) ||
            (!Player2.pokemonsInHand[0].live && !Player2.pokemonsInHand[1].live && !Player2.pokemonsInHand[2].live || !Player2.SkipsLeft))
            {
                if (!Player1.pokemonsInHand[0].live && !Player1.pokemonsInHand[1].live && !Player1.pokemonsInHand[2].live || !Player1.SkipsLeft)
                {
                    DrawTextWithOutline("Player 2 won!", RES_W*2-140, RES_H*2-20, 4, 40, BLACK, RED);

                }
                if (!Player2.pokemonsInHand[0].live && !Player2.pokemonsInHand[1].live && !Player2.pokemonsInHand[2].live || !Player2.SkipsLeft)
                {
                    DrawTextWithOutline("Player 1 won!", RES_W*2-140, RES_H*2-20, 4, 40, BLACK, GREEN);
                }
            } else
            {

                if (IsKeyPressed(KEY_ENTER))
                {   
                    int expectedHealthOfEnemyACA = enemyOfCurrentPlayer->pokemonsInHand[*enemyOfCurrentPokemonIndex].health-whatDamageCommonAttack;
                    int expectedStaminaOfCurrACA = currentPlayer->pokemonsInHand[*currentPokemonIndex].stamina-staminaCommonAttackUsage; 

                    int expectedHealthOfEnemyASA = enemyOfCurrentPlayer->pokemonsInHand[*enemyOfCurrentPokemonIndex].health-whatDamageSpecialAttack;
                    int expectedStaminaOfCurrASA = currentPlayer->pokemonsInHand[*currentPokemonIndex].stamina-staminaSpecialAttackUsage; 
                

                    if (actionChoice == 0)
                    {
                    
                        if (expectedStaminaOfCurrACA >= 0)
                        {
                            if (expectedHealthOfEnemyACA <= 0)
                            {
                                expectedHealthOfEnemyACA = 0;
                                enemyOfCurrentPlayer->pokemonsInHand[*enemyOfCurrentPokemonIndex].live = 0;
                                enemyOfCurrentPlayer->isFirstStep = false;
                            }

                            if (enemyOfCurrentPlayer->pokemonsInHand[*enemyOfCurrentPokemonIndex].health >= 0)
                            {
                                currentPlayer->pokemonsInHand[*currentPokemonIndex].stamina = expectedStaminaOfCurrACA;
                                enemyOfCurrentPlayer->pokemonsInHand[*enemyOfCurrentPokemonIndex].health = expectedHealthOfEnemyACA;

                                whoGoes = !whoGoes;
                                if (currentPlayer->isFirstStep)
                                {
                                    currentPlayer->isFirstStep = false;
                                    isInitFirstStep = false;
                                    
                                }
                                PlaySound(currentPlayer->PokemonsSound[*currentPokemonIndex]);
                            }
                        }
                        
                    }

                    if (actionChoice == 1)
                    {

                        if (expectedStaminaOfCurrASA >= 0)
                        {
                            if (expectedHealthOfEnemyASA <= 0)
                            {
                                expectedHealthOfEnemyASA = 0;
                                enemyOfCurrentPlayer->pokemonsInHand[*enemyOfCurrentPokemonIndex].live = 0;
                                enemyOfCurrentPlayer->isFirstStep = false;
                            }

                            if (enemyOfCurrentPlayer->pokemonsInHand[*enemyOfCurrentPokemonIndex].health >= 0)
                            {
                                currentPlayer->pokemonsInHand[*currentPokemonIndex].stamina = expectedStaminaOfCurrASA;
                                enemyOfCurrentPlayer->pokemonsInHand[*enemyOfCurrentPokemonIndex].health = expectedHealthOfEnemyASA;

                                whoGoes = !whoGoes;
                                if (currentPlayer->isFirstStep)
                                {
                                    currentPlayer->isFirstStep = false;
                                    isInitFirstStep = false;
                                    
                                }
                                PlaySound(currentPlayer->PokemonsSound[*currentPokemonIndex]);
                            }
                        }
                        
                    }

                    if (actionChoice == 2)
                    {
                        if (currentPlayer->pokemonsInHand[*currentPokemonIndex].regen_left)
                        {
                            currentPlayer->pokemonsInHand[*currentPokemonIndex].health = (currentPlayer->pokemonsInHand[*currentPokemonIndex].max_health > (int)((float)currentPlayer->pokemonsInHand[*currentPokemonIndex].health+currentPlayer->pokemonsInHand[*currentPokemonIndex].max_health*currentPlayer->pokemonsInHand[*currentPokemonIndex].regeneration_coefficient) ? (currentPlayer->pokemonsInHand[*currentPokemonIndex].health+(int)((float)currentPlayer->pokemonsInHand[*currentPokemonIndex].max_health*currentPlayer->pokemonsInHand[*currentPokemonIndex].regeneration_coefficient)) : currentPlayer->pokemonsInHand[*currentPokemonIndex].max_health);
                            currentPlayer->pokemonsInHand[*currentPokemonIndex].regen_left = 0;
                            whoGoes = !whoGoes;
                            if (currentPlayer->isFirstStep)
                            {
                                currentPlayer->isFirstStep = false;
                                isInitFirstStep = false;
                            }
                            PlaySound(currentPlayer->PokemonsSound[*currentPokemonIndex]);
                        }

                    }

                    if (actionChoice == 3)
                    {
                        whoGoes = !whoGoes;
                        if (currentPlayer->isFirstStep)
                        {
                            currentPlayer->isFirstStep = false;
                            isInitFirstStep = false;
                        }
                        currentPlayer->SkipsLeft--;
                    }
                    
                    
                }
                if (actionChoice == 4)
                {
                    changePokemon();
                }

                DrawHealthBarsDuringTheFight();
            }
                
        } else
        {
            // ? 

            // init pokemons
            if (!initPokemons)
            {
                YourPokemon = Pokemons[currentChoice];
                EnemyPokemon = Pokemons[enemyIndex];
                initPokemons = 1;
            }

            DrawTexturePro(PokemonsBack[currentChoice], { 0.0f, 0.0f, 96.0f, 96.0f }, { (RES_W/2-80)*4.0f, (RES_H/2-50)*4.0f, 96*4.0f, 96*4.0f }, Vector2Zero(), 0, WHITE);
            DrawTexturePro(PokemonsFront[enemyIndex], { 0.0f, 0.0f, 96.0f, 96.0f }, { (RES_W/2-20)*4.0f, (RES_H/2-90)*4.0f, 96*4.0f, 96*4.0f }, Vector2Zero(), 0, WHITE);
            float YourMultiplier = MatrixPokemons[(int)YourPokemon.type_pokemon.type_pokemon][(int)EnemyPokemon.type_pokemon.type_pokemon];
            int YourDamageCommonAttack = YourPokemon.atk-(int)(EnemyPokemon.def*YourMultiplier);
            YourDamageCommonAttack = (YourDamageCommonAttack > 0) ? YourDamageCommonAttack : 0;

            int YourDamageSpecialAttack = YourPokemon.sp_atk-(int)(EnemyPokemon.sp_def*YourMultiplier);
            YourDamageSpecialAttack = (YourDamageSpecialAttack > 0) ? YourDamageSpecialAttack : 0;

            int YourStaminaCommonAttackUsage = YourPokemon.stamina_atk_usage;
            int YourStaminaSpecialAttackUsage = YourPokemon.stamina_sp_atk_usage;

            float EnemyMultiplier = MatrixPokemons[(int)EnemyPokemon.type_pokemon.type_pokemon][(int)YourPokemon.type_pokemon.type_pokemon];
            int EnemyDamageCommonAttack = EnemyPokemon.atk-(int)(YourPokemon.def*EnemyMultiplier);
            EnemyDamageCommonAttack = (EnemyDamageCommonAttack > 0) ? EnemyDamageCommonAttack : 0;

            int EnemyDamageSpecialAttack = EnemyPokemon.sp_atk-(int)(YourPokemon.sp_def*EnemyMultiplier);
            EnemyDamageSpecialAttack = (EnemyDamageSpecialAttack > 0) ? EnemyDamageSpecialAttack : 0;

            int EnemyStaminaCommonAttackUsage = EnemyPokemon.stamina_atk_usage;
            int EnemyStaminaSpecialAttackUsage = EnemyPokemon.stamina_sp_atk_usage;

            vector <string> actions = {
                "Attack",
                "Special attack",
                "Regeneration"
            };

            if (!whoGoes)
            {
                if (IsKeyPressed(KEY_W))
                {
                    actionChoice--;
                    if (actionChoice < 0)
                    {
                        actionChoice = actions.size()-1;
                    }
                }
                if (IsKeyPressed(KEY_S))
                {
                    actionChoice++;
                    if (actionChoice > actions.size()-1)
                    {
                        actionChoice = 0;
                    }
                }
            }

            DrawText("Choose action:", (RES_W/2)*4-285, (RES_H/2)*4+280-42, 10*2, BLACK);
            
            DrawText("HP (damage)", (RES_W/2)*4-100, (RES_H/2)*4+280-42, 10*2, Color{ 153, 0, 0, 255 });

            DrawText("Stamina usage", (RES_W/2)*4+30, (RES_H/2)*4+280-42, 10*2, Color{ 0, 102, 102, 255 });

            activeColorFrame++;

            for (int i = 0; i < actions.size(); i++)
            {

                if (i == 0)
                {
                    DrawText((to_string(i+1)+". "+actions[i]).c_str(), (RES_W/2)*4-285, (RES_H/2)*4+280-21+18*i, 10*2, ((activeColorFrame/10)%2 && i == actionChoice) ? YELLOW : BLACK);
                    
                    // how many damage gets enemy after common attack
                    DrawText(TextFormat("%i", YourDamageCommonAttack), (RES_W/2)*4-50, (RES_H/2)*4+280-21+18*i, 10*2, ((activeColorFrame/10)%2 && i == actionChoice) ? YELLOW : Color{ 153, 0, 0, 255 });


                    DrawText(TextFormat("%i", YourStaminaCommonAttackUsage), (RES_W/2)*4+80, (RES_H/2)*4+280-21+18*i, 10*2, ((activeColorFrame/10)%2 && i == actionChoice) ? YELLOW : Color{ 0, 102, 102, 255 });
                } else if (i == 1)
                {
                    DrawText((to_string(i+1)+". "+actions[i]).c_str(), (RES_W/2)*4-285, (RES_H/2)*4+280-21+18*i, 10*2, ((activeColorFrame/10)%2 && i == actionChoice) ? YELLOW : BLACK);
                    
                    // how many damage gets enemy after special attack
                    DrawText(TextFormat("%i", YourDamageSpecialAttack), (RES_W/2)*4-50, (RES_H/2)*4+280-21+18*i, 10*2, ((activeColorFrame/10)%2 && i == actionChoice) ? YELLOW : Color{ 153, 0, 0, 255 });


                    DrawText(TextFormat("%i", YourStaminaSpecialAttackUsage), (RES_W/2)*4+80, (RES_H/2)*4+280-21+18*i, 10*2, ((activeColorFrame/10)%2 && i == actionChoice) ? YELLOW : Color{ 0, 102, 102, 255 });
                } else if (i == 2)
                {
                    DrawText((to_string(i+1)+". "+actions[i]+" (left: "+to_string(YourPokemon.regen_left)+"/1, ret. "+ TextFormat("%0.0lf", (float)(YourPokemon.regeneration_coefficient*100))+"% from max health)").c_str(), (RES_W/2)*4-285, (RES_H/2)*4+280-21+18*i, 10*2, ((activeColorFrame/10)%2 && i == actionChoice) ? YELLOW : BLACK); 
                }

            }


            int expectedHealthOfEnemyACA = EnemyPokemon.health-YourDamageCommonAttack;
            int expectedStaminaOfCurrACA = YourPokemon.stamina-YourStaminaCommonAttackUsage; 

            int expectedHealthOfEnemyASA = EnemyPokemon.health-YourDamageSpecialAttack;
            int expectedStaminaOfCurrASA = YourPokemon.stamina-YourStaminaSpecialAttackUsage; 
        
        
            int expectedHealthOfCurrACA = YourPokemon.health-EnemyDamageCommonAttack;
            int expectedStaminaOfEnemyACA = EnemyPokemon.stamina-EnemyStaminaCommonAttackUsage; 

            int expectedHealthOfCurrASA = YourPokemon.health-EnemyDamageSpecialAttack;
            int expectedStaminaOfEnemyASA = EnemyPokemon.stamina-EnemyStaminaSpecialAttackUsage; 
            
            if (
                !EnemyPokemon.live || !YourPokemon.live || 
                (expectedStaminaOfCurrACA <= 0 && expectedStaminaOfCurrASA <= 0) ||
                (expectedStaminaOfEnemyACA <= 0 && expectedStaminaOfEnemyASA <= 0)
            )
            {
                if (!EnemyPokemon.live || (expectedStaminaOfEnemyACA < 0 && expectedStaminaOfEnemyASA < 0))
                {
                    DrawTextWithOutline("You won!", RES_W*2-60, RES_H*2-50, 4, 40, BLACK, GREEN);
                } else
                if (!YourPokemon.live || (expectedStaminaOfCurrACA < 0 && expectedStaminaOfCurrASA < 0))
                {
                    DrawTextWithOutline("You lost!", RES_W*2-60, RES_H*2-50, 4, 40, BLACK, RED);
                }

            } else
            {
                if (!whoGoes)
                {
                    if (IsKeyPressed(KEY_ENTER))
                    {
                        if (actionChoice == 0)
                        {
                            if (expectedStaminaOfCurrACA >= 0)
                            {
                                if (expectedHealthOfEnemyACA <= 0)
                                {
                                    expectedHealthOfEnemyACA = 0;
                                    EnemyPokemon.live = 0;
                                }

                                if (EnemyPokemon.health >= 0)
                                {
                                    YourPokemon.stamina = expectedStaminaOfCurrACA;
                                    EnemyPokemon.health = expectedHealthOfEnemyACA;

                                    whoGoes = !whoGoes;

                                    PlaySound(PokemonsSound[currentChoice]);
                                }
                            }

                        }
                        if (actionChoice == 1)
                        {
                            if (expectedStaminaOfCurrASA >= 0)
                            {
                                if (expectedHealthOfEnemyASA <= 0)
                                {
                                    expectedHealthOfEnemyASA = 0;
                                    EnemyPokemon.live = 0;
                                }

                                if (EnemyPokemon.health >= 0)
                                {
                                    YourPokemon.stamina = expectedStaminaOfCurrASA;
                                    EnemyPokemon.health = expectedHealthOfEnemyASA;

                                    whoGoes = !whoGoes;
                                    
                                    PlaySound(PokemonsSound[currentChoice]);
                                }
                            }
                        }
                        if (actionChoice == 2)
                        {
                            if (YourPokemon.regen_left)
                            {
                                YourPokemon.health = (YourPokemon.max_health > (int)((float)YourPokemon.health+(float)(YourPokemon.max_health)*YourPokemon.regeneration_coefficient) ? (YourPokemon.health+(int)((float)YourPokemon.max_health*YourPokemon.regeneration_coefficient)) : YourPokemon.max_health);
                                YourPokemon.regen_left = 0;
                                whoGoes = !whoGoes;
                                PlaySound(PokemonsSound[currentChoice]);
                            }

                        }
                    }
                } else
                {
                    if (!gotTime)
                    {
                        timeGap = GetTime();
                        gotTime = 1;
                    }

                    double NewTime = GetTime();
                    
                    if (NewTime - timeGap > (double)1.5) 
                    {    
                        if (expectedStaminaOfEnemyACA < 0 && expectedStaminaOfEnemyASA < 0)
                        {
                            EnemyPokemon.health = 0;
                            EnemyPokemon.live = 0;
                            whoGoes = !whoGoes;
                        } else
                        {
                            if (expectedStaminaOfEnemyACA >= 0)
                                actionChoice = 0;
                            if (expectedStaminaOfEnemyASA >= 0)
                                actionChoice = 1;
                            if (EnemyPokemon.health <= (EnemyPokemon.max_health*0.2))
                            {
                                actionChoice = 2;
                            }
                        }

                        if (actionChoice == 0)
                        {
                            if (expectedStaminaOfEnemyACA >= 0)
                            {
                                if (expectedHealthOfCurrACA <= 0)
                                {
                                    expectedHealthOfCurrACA = 0;
                                    YourPokemon.live = 0;
                                }

                                if (YourPokemon.health >= 0)
                                {
                                    EnemyPokemon.stamina = expectedStaminaOfEnemyACA;
                                    YourPokemon.health = expectedHealthOfCurrACA;

                                    whoGoes = !whoGoes;

                                    PlaySound(PokemonsSound[enemyIndex]);
                                }
                            }

                        }
                        if (actionChoice == 1)
                        {
                            if (expectedStaminaOfEnemyASA >= 0)
                            {
                                if (expectedHealthOfCurrASA <= 0)
                                {
                                    expectedHealthOfCurrASA = 0;
                                    YourPokemon.live = 0;
                                }

                                if (YourPokemon.health >= 0)
                                {
                                    EnemyPokemon.stamina = expectedStaminaOfEnemyASA;
                                    YourPokemon.health = expectedHealthOfCurrASA;

                                    whoGoes = !whoGoes;
                                    
                                    PlaySound(PokemonsSound[enemyIndex]);
                                }
                            }
                        }
                        //__
                        
                        if (actionChoice == 2)
                        {
                            if (EnemyPokemon.regen_left)
                            {
                                EnemyPokemon.health = (EnemyPokemon.max_health > (int)((float)EnemyPokemon.health+(float)(EnemyPokemon.max_health)*EnemyPokemon.regeneration_coefficient) ? (EnemyPokemon.health+(int)((float)EnemyPokemon.max_health*EnemyPokemon.regeneration_coefficient)) : EnemyPokemon.max_health);
                                EnemyPokemon.regen_left = 0;
                                whoGoes = !whoGoes;

                                PlaySound(PokemonsSound[enemyIndex]);
                            }

                        }
                        gotTime = 0;
                    }

                } 

            }

            string currentType;
            Color currentColorOfType;

            switch (YourPokemon.type_pokemon.type_pokemon)
            {
                case BasicPokemonType::ELECTRIC:
                    currentType = "ELECTRIC";
                    currentColorOfType = YELLOW;
                    break;
                case BasicPokemonType::WATER:
                    currentType = "WATER";
                    currentColorOfType = Color{ 45, 164, 255, 255 };
                    break;
                case BasicPokemonType::FLYING:
                    currentType = "FLYING";
                    currentColorOfType = PURPLE;
                    break;
                case BasicPokemonType::FAIRY:
                    currentType = "FAIRY";
                    currentColorOfType = PINK;
                    break;
                case BasicPokemonType::FIRE:
                    currentType = "FIRE";
                    currentColorOfType = ORANGE;
                    break;
                case BasicPokemonType::BUG:
                    currentType = "BUG";
                    currentColorOfType = Color{ 45, 255, 237, 255 };
                    break;
                case BasicPokemonType::GRASS:
                    currentType = "GRASS";
                    currentColorOfType = Color{ 65, 255, 45, 255 };
                    break;
                default:
                    currentType = "NORMAL";
                    currentColorOfType = WHITE;
                    break;
            } 

            Rectangle src;
            src.height = 43.0f;
            src.width = 148.0f;
            src.x = 0.0f;
            src.y = 0.0f;

            Rectangle dest;
            dest.height = 43*2.0f;
            dest.width = 148*2.0f;
            dest.x = (RES_W/2)*4.0f;
            dest.y = (RES_H/2)*4.0f;             

            if (YourPokemon.live)
            {
                if (!whoGoes)
                {
                    DrawTextWithOutline((YourPokemon.name_pokemon+" goes"), (RES_W/2-70)*4,(RES_H/2+42)*4, 2, 10*2, BLACK, currentColorOfType);
                }

                DrawTexturePro((!whoGoes) ? healthBarActive : healthBar, src, dest, Vector2Zero(), 0, WHITE);
                DrawText(YourPokemon.name_pokemon.c_str(), (RES_W/2)*4.0f+56, (RES_H/2)*4.0f-42+60, 10*2, Color{ 228, 240, 240, 255});

                DrawRectangle((RES_W/2)*4.0f+280-currentType.length()*14, (RES_H/2)*4.0f-42+60, currentType.length()*14+4, 18, BLACK);
                DrawText(currentType.c_str(), (RES_W/2)*4.0f+282-currentType.length()*14, dest.y+18, 10*2, currentColorOfType);
                
                DrawRectangle(dest.x+44, dest.y+78, 121*YourPokemon.stamina/YourPokemon.max_stamina*2, 2, Color{ 0, 220, 220, 255 });
                DrawRectangle(dest.x+44, dest.y+78+2, 121*YourPokemon.stamina/YourPokemon.max_stamina*2, 2, Color{ 0, 180, 180, 255 });
                
                //shadow
                DrawText(TextFormat("%i", YourPokemon.stamina), dest.x+157, dest.y+60, 8*2, BLACK);
                DrawText(TextFormat("%i", YourPokemon.max_stamina), dest.x+157+34, dest.y+60, 8*2, BLACK);

                DrawText(TextFormat("%i", YourPokemon.stamina), dest.x+156, dest.y+59, 8*2, Color{ 0, 220, 220, 255 });
                DrawText(TextFormat("%i", YourPokemon.max_stamina), dest.x+156+34, dest.y+59, 8*2, Color{ 0, 220, 220, 255 });

                DrawRectangle(dest.x+140, dest.y+48, 73*YourPokemon.health/YourPokemon.max_health*2, 2, Color{ 255, 96, 98, 255 });
                DrawRectangle(dest.x+140, dest.y+48+2, 73*YourPokemon.health/YourPokemon.max_health*2, 2, Color{ 231, 68, 70, 255 });

                //shadow
                DrawText(TextFormat("%i", YourPokemon.health), dest.x+225, dest.y+60, 8*2, BLACK);
                DrawText(TextFormat("%i", YourPokemon.max_health), dest.x+225+34, dest.y+60, 8*2, BLACK);

                DrawText(TextFormat("%i", YourPokemon.health), dest.x+224, dest.y+59, 8*2, Color{ 255, 96, 98, 255 });
                DrawText(TextFormat("%i", YourPokemon.max_health), dest.x+224+34, dest.y+59, 8*2, Color{ 255, 96, 98, 255 });

            } else
            {
                src.width = 48.0f;
                src.x = 0.0f; 
                dest.width = 96.0f; 
                dest.x += 200.0f;
                DrawTexturePro(healthBar, src, dest, Vector2Zero(), 0, WHITE); 
                if (YourPokemon.live == 0)
                {
                    DrawTexturePro(deadSkull, {0.0f, 0.0f, 10.0f, 10.0f}, {dest.x+40.0f, dest.y+10.0f, 20.0f, 20.0f}, Vector2Zero(), 0, WHITE);
                }
            }

            switch (EnemyPokemon.type_pokemon.type_pokemon)
            {
                case BasicPokemonType::ELECTRIC:
                    currentType = "ELECTRIC";
                    currentColorOfType = YELLOW;
                    break;
                case BasicPokemonType::WATER:
                    currentType = "WATER";
                    currentColorOfType = Color{ 45, 164, 255, 255 };
                    break;
                case BasicPokemonType::FLYING:
                    currentType = "FLYING";
                    currentColorOfType = PURPLE;
                    break;
                case BasicPokemonType::FAIRY:
                    currentType = "FAIRY";
                    currentColorOfType = PINK;
                    break;
                case BasicPokemonType::FIRE:
                    currentType = "FIRE";
                    currentColorOfType = ORANGE;
                    break;
                case BasicPokemonType::BUG:
                    currentType = "BUG";
                    currentColorOfType = Color{ 45, 255, 237, 255 };
                    break;
                case BasicPokemonType::GRASS:
                    currentType = "GRASS";
                    currentColorOfType = Color{ 65, 255, 45, 255 };
                    break;
                default:
                    currentType = "NORMAL";
                    currentColorOfType = WHITE;
                    break;
            }    

            src.height = 43.0f;
            src.width = 148.0f;
            src.x = 0.0f;
            src.y = 0.0f;


            dest.height = 43*2.0f;
            dest.width = 148*2.0f;
            dest.x = (RES_W/2)*4.0f-296;
            dest.y = (RES_H/2)*4.0f-200;
            
            if (EnemyPokemon.live)
            {
                if (whoGoes)
                {
                    DrawTextWithOutline((EnemyPokemon.name_pokemon+" goes"), (RES_W/2+20)*4+20,(RES_H/2)*4-290, 2, 10*2, BLACK, currentColorOfType);
                }
                

                DrawTexturePro((whoGoes) ? healthBarEnemyActive : healthBarEnemy, src, dest, Vector2Zero(), 0, WHITE);
                DrawText(EnemyPokemon.name_pokemon.c_str(), dest.x+12, dest.y+16, 10*2, Color{ 228, 240, 240, 255 });

                DrawRectangle(dest.x+250-currentType.length()*14, dest.y+14, currentType.length()*14+4, 18, BLACK);
                DrawText(currentType.c_str(), (RES_W/2)*4.0f-44-currentType.length()*14, dest.y+14, 10*2, currentColorOfType);

                DrawRectangle(dest.x+14, dest.y+78, 121*EnemyPokemon.stamina/EnemyPokemon.max_stamina*2, 2, Color{ 0, 220, 220, 255 });
                DrawRectangle(dest.x+14, dest.y+78+2, 121*EnemyPokemon.stamina/EnemyPokemon.max_stamina*2, 2, Color{ 0, 180, 180, 255 });

                //shadow
                DrawText(TextFormat("%i", EnemyPokemon.stamina), dest.x+25, dest.y+60, 8*2, BLACK);
                DrawText(TextFormat("%i", EnemyPokemon.max_stamina), dest.x+59, dest.y+60, 8*2, BLACK);

                DrawText(TextFormat("%i", EnemyPokemon.stamina), dest.x+24, dest.y+59, 8*2, Color{ 0, 220, 220, 255 });
                DrawText(TextFormat("%i", EnemyPokemon.max_stamina), dest.x+58, dest.y+59, 8*2, Color{ 0, 220, 220, 255 });

                DrawRectangle(dest.x+14, dest.y+48, 73*EnemyPokemon.health/EnemyPokemon.max_health*2, 2, Color{ 255, 96, 98, 255 });
                DrawRectangle(dest.x+14, dest.y+48+2, 73*EnemyPokemon.health/EnemyPokemon.max_health*2, 2, Color{ 231, 68, 70, 255 });

                //shadow
                DrawText(TextFormat("%i", EnemyPokemon.health), dest.x+93, dest.y+60, 8*2, BLACK);
                DrawText(TextFormat("%i", EnemyPokemon.max_health), dest.x+93+34, dest.y+60, 8*2, BLACK);

                DrawText(TextFormat("%i", EnemyPokemon.health), dest.x+92, dest.y+59, 8*2, Color{ 255, 96, 98, 255 });
                DrawText(TextFormat("%i", EnemyPokemon.max_health), dest.x+92+34, dest.y+59, 8*2, Color{ 255, 96, 98, 255 });

            } else
            {
                src.width = 48.0f;
                src.x = 100.0f; 
                dest.width = 96.0f; 
                DrawTexturePro(healthBarEnemy, src, dest, Vector2Zero(), 0, WHITE); 
                
                if (EnemyPokemon.live == 0)
                {
                    DrawTexturePro(deadSkull, {0.0f, 0.0f, 10.0f, 10.0f}, {dest.x+40.0f, dest.y+10.0f, 20.0f, 20.0f}, Vector2Zero(), 0, WHITE);
                }
            }

            


        }

        
    }


    // DrawText((paths).c_str(), 0, RES_H+100, 10*2, BLACK);   
    
    // const char* text1 = (char*)camera_x;
    // DrawText(TextFormat("%f", player.x), 16, 16, 20*2, BLACK);
    // DrawText(TextFormat("%f", player.y), 16, 40, 20*2, BLACK);
}

void changePokemonInWhoIsActive(FightParticipant *P, int choice)
{
    for (int i = 0; i < 3; i++)
    {
        if (P->whoIsActive[i])
        {
            P->whoIsActive[i] = 0;
        }
        if (i == choice)
        {
            P->whoIsActive[i] = 1;
        }
    }
}

void changePokemon()
{
    if (IsKeyPressed(KEY_ENTER) && !isChangingPokemon && !isInitFirstStep)
    {
        isChangingPokemon = 1;
        entry2 = false;
    }

    if (isChangingPokemon)
    {
        if (currentPlayer->pokemonsInHand[currentChangeChoice].live)
        {
            changePokemonInWhoIsActive(currentPlayer, currentChangeChoice);
            *currentPokemonIndex = currentChangeChoice;
        }
        if (IsKeyPressed(KEY_ENTER) && entry2)
        {
            whoGoes = !whoGoes;

            isChangingPokemon = 0;
        } 
        entry2 = true;
    }
}

void DrawTextWithOutline(string Text, int posX, int posY, 
int thickness, int fontSize, Color outlineColor, Color textColor)
{
    DrawText((Text).c_str(), posX+thickness, posY+thickness, fontSize, outlineColor);
    DrawText((Text).c_str(), posX-thickness, posY-thickness, fontSize, outlineColor);
    DrawText((Text).c_str(), posX+thickness, posY-thickness, fontSize, outlineColor);
    DrawText((Text).c_str(), posX-thickness, posY+thickness, fontSize, outlineColor);

    DrawText((Text).c_str(), posX+thickness, posY, fontSize, outlineColor);
    DrawText((Text).c_str(), posX-thickness, posY, fontSize, outlineColor);
    DrawText((Text).c_str(), posX, posY+thickness, fontSize, outlineColor);
    DrawText((Text).c_str(), posX, posY-thickness, fontSize, outlineColor);
    DrawText((Text).c_str(), posX, posY, fontSize, textColor);
}

void DrawHealthBarsDuringTheFight()
{
    int rowCounter = 0;
    int rowHeight = 90;
    
    // drawing health bar for the first player
    for (int i = 0; i < 3; i++)
    {
        string currentType;
        Color currentColorOfType;
        switch (Player1.pokemonsInHand[i].type_pokemon.type_pokemon)
        {
            case BasicPokemonType::ELECTRIC:
                currentType = "ELECTRIC";
                currentColorOfType = YELLOW;
                break;
            case BasicPokemonType::WATER:
                currentType = "WATER";
                currentColorOfType = Color{ 45, 164, 255, 255 };
                break;
            case BasicPokemonType::FLYING:
                currentType = "FLYING";
                currentColorOfType = PURPLE;
                break;
            case BasicPokemonType::FAIRY:
                currentType = "FAIRY";
                currentColorOfType = PINK;
                break;
            case BasicPokemonType::FIRE:
                currentType = "FIRE";
                currentColorOfType = ORANGE;
                break;
            case BasicPokemonType::BUG:
                currentType = "BUG";
                currentColorOfType = Color{ 45, 255, 237, 255 };
                break;
            case BasicPokemonType::GRASS:
                currentType = "GRASS";
                currentColorOfType = Color{ 65, 255, 45, 255 };
                break;
            default:
                currentType = "NORMAL";
                currentColorOfType = WHITE;
                break;
        } 

        Rectangle src;
        src.height = 43.0f;
        src.width = 148.0f;
        src.x = 0.0f;
        src.y = 0.0f;

        Rectangle dest;
        dest.height = 43*2.0f;
        dest.width = 148*2.0f;
        dest.x = (RES_W/2)*4.0f;
        dest.y = (RES_H/2)*4.0f-60+rowHeight*rowCounter;                

        if (Player1.whoIsActive[i] && Player1.pokemonsInHand[i].live)
        {
            if (!whoGoes)
            {
                DrawTextWithOutline((Player1.pokemonsInHand[i].name_pokemon+" goes"), (RES_W/2-70)*4,(RES_H/2+42)*4, 2, 10*2, BLACK, currentColorOfType);
            }

            DrawTexturePro((Player1.whoIsActive[i] && !whoGoes) ? healthBarActive : healthBar, src, dest, Vector2Zero(), 0, WHITE);
            DrawText(Player1.pokemonsInHand[i].name_pokemon.c_str(), (RES_W/2)*4.0f+56, (RES_H/2)*4.0f-42+rowHeight*rowCounter, 10*2, Color{ 228, 240, 240, 255});

            DrawRectangle((RES_W/2)*4.0f+280-currentType.length()*14, (RES_H/2)*4.0f-42+rowHeight*rowCounter, currentType.length()*14+4, 18, BLACK);
            DrawText(currentType.c_str(), (RES_W/2)*4.0f+282-currentType.length()*14, (RES_H/2)*4.0f-42+rowHeight*rowCounter, 10*2, currentColorOfType);
            
            DrawRectangle(dest.x+44, dest.y+78, 121*Player1.pokemonsInHand[i].stamina/Player1.pokemonsInHand[i].max_stamina*2, 2, Color{ 0, 220, 220, 255 });
            DrawRectangle(dest.x+44, dest.y+78+2, 121*Player1.pokemonsInHand[i].stamina/Player1.pokemonsInHand[i].max_stamina*2, 2, Color{ 0, 180, 180, 255 });
            
            //shadow
            DrawText(TextFormat("%i", Player1.pokemonsInHand[i].stamina), dest.x+157, dest.y+60, 8*2, BLACK);
            DrawText(TextFormat("%i", Player1.pokemonsInHand[i].max_stamina), dest.x+157+34, dest.y+60, 8*2, BLACK);

            DrawText(TextFormat("%i", Player1.pokemonsInHand[i].stamina), dest.x+156, dest.y+59, 8*2, Color{ 0, 220, 220, 255 });
            DrawText(TextFormat("%i", Player1.pokemonsInHand[i].max_stamina), dest.x+156+34, dest.y+59, 8*2, Color{ 0, 220, 220, 255 });

            DrawRectangle(dest.x+140, dest.y+48, 73*Player1.pokemonsInHand[i].health/Player1.pokemonsInHand[i].max_health*2, 2, Color{ 255, 96, 98, 255 });
            DrawRectangle(dest.x+140, dest.y+48+2, 73*Player1.pokemonsInHand[i].health/Player1.pokemonsInHand[i].max_health*2, 2, Color{ 231, 68, 70, 255 });

            //shadow
            DrawText(TextFormat("%i", Player1.pokemonsInHand[i].health), dest.x+225, dest.y+60, 8*2, BLACK);
            DrawText(TextFormat("%i", Player1.pokemonsInHand[i].max_health), dest.x+225+34, dest.y+60, 8*2, BLACK);

            DrawText(TextFormat("%i", Player1.pokemonsInHand[i].health), dest.x+224, dest.y+59, 8*2, Color{ 255, 96, 98, 255 });
            DrawText(TextFormat("%i", Player1.pokemonsInHand[i].max_health), dest.x+224+34, dest.y+59, 8*2, Color{ 255, 96, 98, 255 });
            rowCounter++;

            DrawTexturePro(Player1.PokemonsBack[i], { 0.0f, 0.0f, 96.0f, 96.0f }, { (RES_W/2-80)*4.0f, (RES_H/2-50)*4.0f, 96*4.0f, 96*4.0f }, Vector2Zero(), 0, WHITE);
        } else
        {
            src.width = 48.0f;
            src.x = 0.0f; 
            dest.width = 96.0f; 
            dest.x += 200.0f;
            DrawTexturePro(Player1.whoIsActive[i] ? healthBarActive : healthBar, src, dest, Vector2Zero(), 0, WHITE); 
            rowCounter++;
            if (Player1.pokemonsInHand[i].live == 0)
            {
                DrawTexturePro(deadSkull, {0.0f, 0.0f, 10.0f, 10.0f}, {dest.x+40.0f, dest.y+10.0f, 20.0f, 20.0f}, Vector2Zero(), 0, WHITE);
            }
        }

        

    
    }

    rowCounter = 0;
    // drawing health bar for the second player
    for (int i = 0; i < 3; i++)
    {
        string currentType;
        Color currentColorOfType;
        switch (Player2.pokemonsInHand[i].type_pokemon.type_pokemon)
        {
            case BasicPokemonType::ELECTRIC:
                currentType = "ELECTRIC";
                currentColorOfType = YELLOW;
                break;
            case BasicPokemonType::WATER:
                currentType = "WATER";
                currentColorOfType = Color{ 45, 164, 255, 255 };
                break;
            case BasicPokemonType::FLYING:
                currentType = "FLYING";
                currentColorOfType = PURPLE;
                break;
            case BasicPokemonType::FAIRY:
                currentType = "FAIRY";
                currentColorOfType = PINK;
                break;
            case BasicPokemonType::FIRE:
                currentType = "FIRE";
                currentColorOfType = ORANGE;
                break;
            case BasicPokemonType::BUG:
                currentType = "BUG";
                currentColorOfType = Color{ 45, 255, 237, 255 };
                break;
            case BasicPokemonType::GRASS:
                currentType = "GRASS";
                currentColorOfType = Color{ 65, 255, 45, 255 };
                break;
            default:
                currentType = "NORMAL";
                currentColorOfType = WHITE;
                break;
        }    
        Rectangle src;
        src.height = 43.0f;
        src.width = 148.0f;
        src.x = 0.0f;
        src.y = 0.0f;

        Rectangle dest;
        dest.height = 43*2.0f;
        dest.width = 148*2.0f;
        dest.x = (RES_W/2)*4.0f-296;
        dest.y = (RES_H/2)*4.0f-376+rowHeight*rowCounter;
        
        if (Player2.whoIsActive[i] && Player2.pokemonsInHand[i].live)
        {
            if (whoGoes)
            {
                DrawTextWithOutline((Player2.pokemonsInHand[i].name_pokemon+" goes"), (RES_W/2+20)*4+20,(RES_H/2)*4-376, 2, 10*2, BLACK, currentColorOfType);
            }
            

            DrawTexturePro((Player2.whoIsActive[i] && whoGoes) ? healthBarEnemyActive : healthBarEnemy, src, dest, Vector2Zero(), 0, WHITE);
            DrawText(Player2.pokemonsInHand[i].name_pokemon.c_str(), dest.x+12, dest.y+16, 10*2, Color{ 228, 240, 240, 255 });

            DrawRectangle(dest.x+250-currentType.length()*14, dest.y+14, currentType.length()*14+4, 18, BLACK);
            DrawText(currentType.c_str(), (RES_W/2)*4.0f-44-currentType.length()*14, dest.y+14, 10*2, currentColorOfType);

            DrawRectangle(dest.x+14, dest.y+78, 121*Player2.pokemonsInHand[i].stamina/Player2.pokemonsInHand[i].max_stamina*2, 2, Color{ 0, 220, 220, 255 });
            DrawRectangle(dest.x+14, dest.y+78+2, 121*Player2.pokemonsInHand[i].stamina/Player2.pokemonsInHand[i].max_stamina*2, 2, Color{ 0, 180, 180, 255 });

            //shadow
            DrawText(TextFormat("%i", Player2.pokemonsInHand[i].stamina), dest.x+25, dest.y+60, 8*2, BLACK);
            DrawText(TextFormat("%i", Player2.pokemonsInHand[i].max_stamina), dest.x+59, dest.y+60, 8*2, BLACK);

            DrawText(TextFormat("%i", Player2.pokemonsInHand[i].stamina), dest.x+24, dest.y+59, 8*2, Color{ 0, 220, 220, 255 });
            DrawText(TextFormat("%i", Player2.pokemonsInHand[i].max_stamina), dest.x+58, dest.y+59, 8*2, Color{ 0, 220, 220, 255 });

            DrawRectangle(dest.x+14, dest.y+48, 73*Player2.pokemonsInHand[i].health/Player2.pokemonsInHand[i].max_health*2, 2, Color{ 255, 96, 98, 255 });
            DrawRectangle(dest.x+14, dest.y+48+2, 73*Player2.pokemonsInHand[i].health/Player2.pokemonsInHand[i].max_health*2, 2, Color{ 231, 68, 70, 255 });

            //shadow
            DrawText(TextFormat("%i", Player2.pokemonsInHand[i].health), dest.x+93, dest.y+60, 8*2, BLACK);
            DrawText(TextFormat("%i", Player2.pokemonsInHand[i].max_health), dest.x+93+34, dest.y+60, 8*2, BLACK);

            DrawText(TextFormat("%i", Player2.pokemonsInHand[i].health), dest.x+92, dest.y+59, 8*2, Color{ 255, 96, 98, 255 });
            DrawText(TextFormat("%i", Player2.pokemonsInHand[i].max_health), dest.x+92+34, dest.y+59, 8*2, Color{ 255, 96, 98, 255 });
            rowCounter++;

            DrawTexturePro(Player2.PokemonsFront[i], { 0.0f, 0.0f, 96.0f, 96.0f }, { (RES_W/2-20)*4.0f, (RES_H/2-90)*4.0f, 96*4.0f, 96*4.0f }, Vector2Zero(), 0, WHITE);
        } else
        {
            src.width = 48.0f;
            src.x = 100.0f; 
            dest.width = 96.0f; 
            DrawTexturePro(Player2.whoIsActive[i] ? healthBarEnemyActive : healthBarEnemy, src, dest, Vector2Zero(), 0, WHITE); 
            rowCounter++;
            if (Player2.pokemonsInHand[i].live == 0)
            {
                DrawTexturePro(deadSkull, {0.0f, 0.0f, 10.0f, 10.0f}, {dest.x+40.0f, dest.y+10.0f, 20.0f, 20.0f}, Vector2Zero(), 0, WHITE);
            }
        }

    }
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
        UnloadSound(PokemonsSound[i]);
    }

    UnloadTexture(enter);
    UnloadTexture(arrow);

    UnloadTexture(buttonE);
    UnloadTexture(buttonF);
    UnloadTexture(buttonH);
    UnloadTexture(buttonA);
    UnloadTexture(buttonD);
    UnloadTexture(buttonW);
    UnloadTexture(buttonS);

    UnloadTexture(healthBar);
    UnloadTexture(healthBarEnemy);
    UnloadTexture(healthBarActive);
    UnloadTexture(healthBarEnemyActive);

    UnloadTexture(fightOverlay);
    UnloadTexture(helpOverlay);

    UnloadMusicStream(music); 
    CloseAudioDevice();
    CloseWindow();
}
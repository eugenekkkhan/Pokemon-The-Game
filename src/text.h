#include "raylib.h"
#include "raymath.h"
#include "game.h"

int HelpOverlayWindowHeight = 620;
int HelpOverlayWindowWidth = 400;

void HelpWindow()
{
    DrawTexture(buttonH, (RES_W-18)*4, (RES_H-35)*4, WHITE);
    DrawText("Exit help", (RES_W-65)*4, (RES_H-35)*4, 20*2, BLACK);

    DrawTexture(helpOverlay, (RES_W/2)*4-HelpOverlayWindowWidth/2+504, (RES_H/2)*4-HelpOverlayWindowHeight/2-90, WHITE);
    
    int rowDist = 20;
    DrawText("?",                                  (RES_W/2)*4-HelpOverlayWindowWidth/2+826, (RES_H/2)*4-HelpOverlayWindowHeight/2-80, 50*2, Color{ 160, 160, 160, 255 });
    DrawText("HP - Heart points",                  (RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*0, 10*2, Color{ 153, 0, 0, 255 });
    DrawText("Atk - Attack",                       (RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*1, 10*2, Color{ 153, 76, 0, 255 });
    DrawText("Def - Defense",                      (RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*2, 10*2, Color{ 0, 110, 55, 255 });
    DrawText("SA - Special attack",                (RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*3, 10*2, Color{ 100, 0, 100, 255 });
    DrawText("SD - Special defense",               (RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*4, 10*2, Color{ 100, 0, 200, 255 });
    DrawText("Spd - Speed",                        (RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*5, 10*2, Color{ 0, 50, 110, 255 });
    DrawText("Stm - Stamina",                      (RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*6, 10*2, Color{ 0, 102, 102, 255 });
    DrawText("SA - Stamina attack usage",          (RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*7, 10*2, Color{ 153, 153, 0, 255 });
    DrawText("SAS - Special Attack Stamina Usage", (RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*8, 10*2, Color{ 204, 0, 102, 255 });
    DrawText("RC - Regeneration coefficient",      (RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*9, 10*2, Color{ 153, 0, 0, 255 });

    DrawText("Speed determines who goes first",(RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*11, 10*2, Color{ 0, 50, 110, 255 }); 

    DrawText("Stamina is like an energy.",(RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*13, 10*2, Color{ 0, 102, 102, 255 }); 
    DrawText("It's used when you attack",(RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*14, 10*2, Color{ 0, 102, 102, 255 });  

    DrawText("Stamina attack usage is how many",(RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*16, 10*2, Color{ 153, 153, 0, 255 });
    DrawText("stamina points you use per attack",(RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*17, 10*2, Color{ 153, 153, 0, 255 });

    DrawText("Special attack stamina usage is", (RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*19, 10*2, Color{ 204, 0, 102, 255 });
    DrawText("how many stamina points you use", (RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*20, 10*2, Color{ 204, 0, 102, 255 });
    DrawText("per one SPECIAL attack", (RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*21, 10*2, Color{ 204, 0, 102, 255 });

    DrawText("During the fight you can use regen.",(RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*23, 10*2, Color{ 153, 0, 0, 255 });
    DrawText("and regeneration coefficient shows",(RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*24, 10*2, Color{ 153, 0, 0, 255 });
    DrawText("what part of your full HP will be",(RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*25, 10*2, Color{ 153, 0, 0, 255 });
    DrawText("recovered",(RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*26, 10*2, Color{ 153, 0, 0, 255 });
    DrawText("(if it's 0, there's no regeneration).",(RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*27, 10*2, Color{ 153, 0, 0, 255 });
    DrawText("Regeneration can be used only once",(RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*28, 10*2, Color{ 153, 0, 0, 255 });
    DrawText("by each pokemon during the battle!",(RES_W/2)*4-HelpOverlayWindowWidth/2+516, (RES_H/2)*4-HelpOverlayWindowHeight/2-80+rowDist*29, 10*2, Color{ 153, 0, 0, 255 });
}

int columnWidth = 45;

int hpColumn = 155;
int atkColumn = hpColumn-columnWidth;
int defColumn = atkColumn-columnWidth;
int spAtkColumn = defColumn-columnWidth;
int spDefColumn = spAtkColumn-columnWidth;
int speedColumn = spDefColumn-columnWidth;
int staminaColumn = speedColumn-columnWidth;
int staminaAtkColumn = staminaColumn-columnWidth;
int staminaSpAtkColumn = staminaAtkColumn-columnWidth;
int regenCoefColumn = staminaSpAtkColumn-columnWidth+4;

void ColNames()
{
    DrawText("Name", (RES_W/2)*4-285, (RES_H/2)*4+280-21, 10*2, GRAY);

    DrawText("HP", (RES_W/2)*4-hpColumn, (RES_H/2)*4+280-21, 10*2, Color{ 153, 0, 0, 255 });

    DrawText("Atk", (RES_W/2)*4-atkColumn, (RES_H/2)*4+280-21, 10*2, Color{ 153, 76, 0, 255 });

    DrawText("Def", (RES_W/2)*4-defColumn, (RES_H/2)*4+280-21, 10*2, Color{ 0, 110, 55, 255 });

    DrawText("SA", (RES_W/2)*4-spAtkColumn, (RES_H/2)*4+280-21, 10*2, Color{ 100, 0, 100, 255 });

    DrawText("SD", (RES_W/2)*4-spDefColumn, (RES_H/2)*4+280-21, 10*2, Color{ 100, 0, 200, 255 });

    DrawText("Spd", (RES_W/2)*4-speedColumn, (RES_H/2)*4+280-21, 10*2, Color{ 0, 50, 110, 255 });

    DrawText("Stm", (RES_W/2)*4-staminaColumn, (RES_H/2)*4+280-21, 10*2, Color{ 0, 102, 102, 255 });

    DrawText("SA", (RES_W/2)*4-staminaAtkColumn, (RES_H/2)*4+280-21, 10*2, Color{ 153, 153, 0, 255 });

    DrawText("SAS", (RES_W/2)*4-staminaSpAtkColumn-7, (RES_H/2)*4+280-21, 10*2, Color{ 204, 0, 102, 255 });
    
    DrawText("RC", (RES_W/2)*4-regenCoefColumn, (RES_H/2)*4+280-21, 10*2, Color{ 153, 0, 0, 255 });
}

void ListOfPokemons()
{
    for (int i = 0; i < 6; i++)
    {
        if (!Pokemons.empty())
        {
            if (i==0)
            {
                int frameColor = activeColorFrame/25;
                Color ComplicatedColorTernaryBlinking = ((frameColor)%2) ? YELLOW : (pokemonsPlayer1[(currentChoice+i)%10] ? GREEN : BLACK);
                Color ComplicatedColorTernary = (pokemonsPlayer1[(currentChoice+i)%10] ? GREEN : BLACK);

                DrawText((Pokemons[(currentChoice+i)%10].name_pokemon).c_str(), (RES_W/2)*4-285, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernaryBlinking);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].health), (RES_W/2)*4-hpColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernaryBlinking);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].atk), (RES_W/2)*4-atkColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernaryBlinking);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].def), (RES_W/2)*4-defColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernaryBlinking);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].sp_atk), (RES_W/2)*4-spAtkColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernaryBlinking);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].sp_def), (RES_W/2)*4-spDefColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernaryBlinking);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].speed), (RES_W/2)*4-speedColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernaryBlinking);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].stamina), (RES_W/2)*4-staminaColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernaryBlinking);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].stamina_atk_usage), (RES_W/2)*4-staminaAtkColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernaryBlinking);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].stamina_sp_atk_usage), (RES_W/2)*4-staminaSpAtkColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernaryBlinking);
                DrawText(TextFormat("%0.2lf", Pokemons[(currentChoice+i)%10].regeneration_coefficient), (RES_W/2)*4-regenCoefColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernaryBlinking);
            } else
            {
                Color ComplicatedColorTernary = (pokemonsPlayer1[(currentChoice+i)%10] ? GREEN : BLACK);

                DrawText((Pokemons[(currentChoice+i)%10].name_pokemon).c_str(), (RES_W/2)*4-285, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernary);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].health), (RES_W/2)*4-hpColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernary);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].atk), (RES_W/2)*4-atkColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernary);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].def), (RES_W/2)*4-defColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernary);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].sp_atk), (RES_W/2)*4-spAtkColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernary);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].sp_def), (RES_W/2)*4-spDefColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernary);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].speed), (RES_W/2)*4-speedColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernary);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].stamina), (RES_W/2)*4-staminaColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernary);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].stamina_atk_usage), (RES_W/2)*4-staminaAtkColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernary);
                DrawText(TextFormat("%i", Pokemons[(currentChoice+i)%10].stamina_sp_atk_usage), (RES_W/2)*4-staminaSpAtkColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernary);
                DrawText(TextFormat("%0.2lf", Pokemons[(currentChoice+i)%10].regeneration_coefficient), (RES_W/2)*4-regenCoefColumn, (RES_H/2)*4+280+18*i, 10*2, ComplicatedColorTernary);
            }
        }

    }
}
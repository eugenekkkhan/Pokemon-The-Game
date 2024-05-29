#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

// MatrixPokemons shows multipliers of defenses depending
// on their type and type of their opponent
// 
// Types      Column shows pokèmon's opponent, 
// |   ↘️      row shows current pokèmon's type.
// ↓    ELE  WAT  FLY  NOR  FAI  FIR  BUG  GRA 
// ELE  1/2   1   1/2   1    1    1    1    1   
// WAT   2   1/2   1    1    1   1/2   1    2  
// FLY   2    1    1    1    1    1   1/2  1/2
// NOR   1    1    1    1    1    1    1    1  
// FAI   1    1    1    1    1    1   1/2   2 
// FIR   1    2    1    1   1/2  1/2  1/2  1/2
// BUG   1    1    2    1    1    2    1   1/2
// GRA  1/2  1/2   2    1   1/2   2    1   1/4
// 
// 
 

enum class BasicPokemonType
{
    ELECTRIC,
    WATER,
    FLYING,
    NORMAL,
    FAIRY,
    FIRE,
    BUG,
    GRASS,
};

struct TypePokemon 
{
	BasicPokemonType type_pokemon;
	double MatrixPokemons[8][8] = {
        { 0.5,   1,   0.5,   1,    1,    1,    1,    1   },   
        {  2,   0.5,   1,    1,    1,   0.5,   1,    2   }, 
        {  2,    1,    1,    1,    1,    1,   0.5,  0.5  },
        {  1,    1,    1,    1,    1,    1,    1,    1   },
        {  1,    1,    1,    1,    1,    1,   0.5,   2   }, 
        {  1,    2,    1,    1,   0.5,  0.5,  0.5,  0.5  },
        {  1,    1,    2,    1,    1,    2,    1,   0.5  },
        { 0.5,  0.5,   2,    1,   0.5,   2,    1,   0.25  }
    };

	TypePokemon(BasicPokemonType basic_type):type_pokemon(basic_type)
	{}
};
// Pokemon  | Type  | HP | Atk | Def  | Sp. Atk | Sp. Def | Speed | Stamina | Stamina Atk | Stamina Sp. Atk | Regeneration | 
// squirtle | WATER | 44 | 48  | 65   | 50      | 64      | 43    | 90      | 15          | 30              | 1/16         |

struct Pokemon 
{

	string name_pokemon="";
	int health = 0;
	int max_health = 0;
	int atk = 0;
    int def = 0;
    int sp_atk = 0;
    int sp_def = 0;
    int speed = 0;
    int stamina = 0;
    int stamina_atk_usage = 0;
    int stamina_sp_atk_usage = 0;
    float regeneration_coefficient = 0;

    bool regen_wasnt_used = true;
	bool live = true;
	
	TypePokemon type_pokemon = BasicPokemonType::NORMAL;

	Pokemon() {};
	Pokemon(string name_pokemon, int health, int atk, int def,
		int sp_atk, int sp_def, int speed, int stamina, 
        int stamina_atk_usage, int stamina_sp_atk_usage, float regeneration_coefficient, 
        TypePokemon type_pokemon);
};

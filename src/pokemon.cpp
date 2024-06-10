#include "pokemon.h"
                                                   
//                                                                                           ↙️ (Special attack stamina usage)
// Pokemon  | Type  | HP | Atk | Def  | Sp. Atk | Sp. Def | Speed | Stamina | Stamina Atk | Stamina Sp. Atk | Regeneration | 
// squirtle | WATER | 44 | 48  | 65   | 50      | 64      | 43    | 90      | 15          | 30              | 1/16         |
//                         ↑     ↑      ↑         ↑         ↑       ↑          ↖️(Default attack stamina usage) ↖ What part of max HP will be regenerated (ONCE USAGE)
//                         |Defense (HP)|         |         |       Stamina is used when you attack
//                         Attack (HP)  |         |         Determines who goes first (white_speed > black_speed -> white_pokemon goes first)
//                                      |         Special Defense (HP damage)
//                                      Special attack (HP damage)

Pokemon::Pokemon(string name_pokemon, int health, int atk, int def,
	int sp_atk, int sp_def, int speed, int stamina, 
    int stamina_atk_usage, int stamina_sp_atk_usage, float regeneration_coefficient, 
    TypePokemon type_pokemon)
    :name_pokemon(name_pokemon), type_pokemon(type_pokemon), health(health), atk(atk), 
    def(def), sp_atk(sp_atk), sp_def(sp_def),
	speed(speed), stamina(stamina), stamina_atk_usage(stamina_atk_usage),
    stamina_sp_atk_usage(stamina_sp_atk_usage), regeneration_coefficient(regeneration_coefficient)
{
	this->max_health = health;
    this->max_stamina = stamina;
}
#include "fight.h"
#include <fstream>

void FightPlayer::Attack(Pokemon* defending_pokemon)
{
    this->ShowAllAttack();
    int temp;
    do {
        std::cout << "���������������� ����������" << std::endl;
        std::cin >> temp;
    } while (temp > this->in_game_pokemon->attacks.size()
        || temp < 0
        || this->in_game_pokemon->energy_pokemon < this->in_game_pokemon->attacks.at(temp).energy_attack);
    defending_pokemon->health -= this->in_game_pokemon->attacks.at(temp).hit_attack;  

}

void FightPlayer::ShowAllAttack()
{
    int index = 0;
    for (struct Attack a : this->in_game_pokemon->attacks)
    {
        std::cout << index++ << " " << a.name_attack << " " << a.hit_attack << " " << a.energy_attack << std::endl;
    }
}

void FightPlayer::AddPokemon(Pokemon pokemon)
{
	this->Pokemons.push_back(pokemon);
	this->count++;
	std::cout << "�������������� ����������������" << std::endl;
}

Pokemon* FightPlayer::TakePokemon(int index)
{
    return &(this->Pokemons.at(index));
}

void FightPlayer::ChangePokemon()
{
}

void FightPlayer::ShowAllPokemonInHand()
{
    int index = 0;
    for (Pokemon a : this->Pokemons)
    {
        std::cout << index++ << " " << a.name_pokemon << " "<< a.health<<std::endl;
    }
}

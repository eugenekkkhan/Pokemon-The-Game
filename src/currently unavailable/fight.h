#include "pokemon.h"

struct FightPlayer {
	std::vector <struct Pokemon> Pokemons;
	struct Pokemon *in_game_pokemon;
	void Attack(Pokemon* defending_pokemon);
	void AddPokemon(Pokemon pokemon);
	Pokemon* TakePokemon(int index);
	void ChangePokemon();
	void ShowAllPokemonInHand();
	void ShowAllAttack();
};

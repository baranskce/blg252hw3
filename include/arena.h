/* @Author
* Student Name: Baran Işık
* Student ID : 150190087
*/
#include <iostream>
#include <pokemon.h>
#include <electricPokemon.h>
#include <psychicPokemon.h>
#pragma once
class Arena{
public:
    Arena();
    void addPokemon(char, std::string, int, int);
    void simulateBattle();
    void spawnTerrain();
    void restartTerrain();
    void printRoundStats(int, int) const;
    void printMatchResults() const;
    
private:
    electricPokemon* electricpoke; // arena has a aggregation to electricPokemon
    psychicPokemon* psychicpoke; // arena has a aggregation to psychicPokemon
    std::string terrain_type[3]; // create a 3 element array
    std::string chosen_terrain;
};
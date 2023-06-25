/* @Author
* Student Name: Baran Işık
* Student ID : 150190087
*/
#include <iostream>
#include <pokemon.h>
#pragma once
class electricPokemon : public Pokemon{
public:
    electricPokemon(char, std::string, int, int);
    int get_chance() const;
    int get_rech() const;

    bool is_fainted() const;
    void set_fainted(bool);
    bool is_powerup();
    void set_powerup(bool);
    bool get_powerup() const;
    bool is_terrain() const;
    void set_terrain(bool);

    void set_recharge(int);
private:
    const int chance;
    int recharge;

    bool fainted; // !! I USE FAINTED AS CONFUSION FOR ELECTRIC POKEMON !!
    bool power_up;
    bool terrain;

};
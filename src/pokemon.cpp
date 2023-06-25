/* @Author
* Student Name: Baran Işık
* Student ID : 150190087
*/
#include <pokemon.h>

// pokemon constructor to use in elec and psy poke constructors
Pokemon::Pokemon(std::string name, char spec, int hp, int dmg):pokename{name}, type{spec}, damage{dmg}, hitpoints{hp}{
                                         }
std::string Pokemon::get_name() const{ //return the name of the pokemon
    return this->pokename;
    }
int Pokemon::get_hp() const{ // get the hp of poke
    return this->hitpoints;
}
int Pokemon::get_damage() const{ // get damage of poke
    return damage;
}
void Pokemon::set_hp(int hit){ // set hp of poke
    this->hitpoints = hit;
}
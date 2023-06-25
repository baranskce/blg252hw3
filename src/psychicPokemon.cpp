/* @Author
* Student Name: Baran Işık
* Student ID : 150190087
*/

#include <pokemon.h>
#include <psychicPokemon.h>

psychicPokemon::psychicPokemon(char type, std::string species, int hp, int dmg)
                                :Pokemon{species, type, hp, dmg} , chance{30}, recharge{0}{ // create the pokemon and initialize the values
                                    terrain = false;
                                    power_up = false;
                                    terrain = false;
                                    std::cout<< "Psychic Pokemon " << species << " has entered the arena." << std:: endl;
                                    std::cout << "Class: Psychic" << std::endl;
                                    std::cout << "\tName: " << species << std::endl;
                                    std::cout << "\tHP: " << hp << std::endl;
                                    std::cout << "\tDamage: " << dmg << std::endl;
                                    std::cout << std::endl;
                                }
 
int psychicPokemon::get_chance() const{
    return chance;
}
int psychicPokemon::get_rech() const{
    return recharge;
}                               
bool psychicPokemon::is_powerup(){ //calculates if power up occurs for given type of poke
    int ch = rand() % 100 + 1; //create a random number between 1-100
    if(get_rech() ==  0){ //if pokemon has recharge to try the power up
        if(ch > get_chance()){ //if not in the given percentage
            set_powerup(false); //no power up
            return false; 
        }else if(ch <= get_chance()){ //if chance is in the given percentage
            set_recharge(5); //set recharge time again to needed turn to be waited
            set_powerup(true); // power up occurs
            return true;
        }
    }else{
        set_recharge((get_rech() - 1)); //if recharge timer is not achieved reduce 1 turn
    }
    set_powerup(false);
    return false;
}
void psychicPokemon::set_powerup(bool pu){
    this->power_up = pu;
}
bool psychicPokemon::get_powerup() const{
    return this->power_up;
}
bool psychicPokemon::is_terrain() const{
    return terrain;
}
void psychicPokemon::set_terrain(bool tf){
    this->terrain = tf;
}
void psychicPokemon::set_recharge(int rch){
    this->recharge = rch;
}

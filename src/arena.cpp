/* @Author
* Student Name: Baran Işık
* Student ID : 150190087
*/

#include "arena.h"


Arena::Arena(){ //set initial terrain types to its array
    terrain_type[0] = "None";
    terrain_type[1] = "electric";
    terrain_type[2] = "psychic";
    chosen_terrain = "reset"; // chosen terrain is reset at first
}

void Arena::addPokemon(char type, std::string species, int hp, int dmg){
    if(type == 'e'){ //if added pokemon is electric
        electricPokemon* elpoke = new electricPokemon(type,species, hp, dmg); //create a new electric pokemon
        this->electricpoke = elpoke;
    }else if(type == 'p'){ //if added pokemon is psychic
        psychicPokemon* psypoke = new psychicPokemon(type,species, hp, dmg); // create a new psychcic pokemon
        this->psychicpoke = psypoke;
    }
}
void Arena::simulateBattle(){

    int round = 1; // round is battle round count
    int counter_fa = 0; // counter for confusion to keep electric pokemons confused time
    int counter_ter = 0; // timer for terrain round (if elec or psy)
    int final_select = 0; //to print last round temporary select counter

    while(electricpoke->get_hp() > 0 && psychicpoke->get_hp() > 0)
    {   
        int select = rand() % 2; // create numbers 0-1 to decide who starts the round
        final_select = select;
        if(counter_fa == 3){ // if elecric pokemon is confuse for last 3 rounds
            electricpoke->set_fainted(false); // reset the confusion time
        }
        if(chosen_terrain == "None" || chosen_terrain == "reset"){ //if terrain type is None or it is the first round of battle
            counter_ter = 0; // terrain counter for electric and psychic set to 0
            spawnTerrain(); // spawn new terrain
        }
        if(counter_ter == 5){ // if electric or psychic terrain reached 5 round it should be resetted
            counter_ter = 0; // reset the counter
            spawnTerrain(); // spawn new terrain
        }
        if(select == 0){ // fight starts with psychic 
            if(electricpoke->is_terrain() || psychicpoke->is_terrain()) // if terrain is elec or psy
                counter_ter++; // increase counter by 1
            if(psychicpoke->is_powerup()){ // if psychic has power up
                if(psychicpoke->is_terrain()){ // if psychic is in its terrain
                    electricpoke->set_fainted(true); // electric poke is confused
                    electricpoke->set_hp(electricpoke->get_hp() - 2*(psychicpoke->get_damage())); // deals 2x damage to elec poke
                    if(electricpoke->get_hp() <= 0){ // if after the hit electric poke lost its life
                        electricpoke->set_hp(0); // set its hp to 0 
                        break;
                    }
                }else{ //if psychic is not in its terrain 
                    if(!electricpoke->is_terrain()) // if terrain is not electric
                        electricpoke->set_fainted(true); // electric poke will be confused 
                    electricpoke->set_hp((electricpoke->get_hp() - psychicpoke->get_damage())); // hit 1x damage to electric poke
                    if(electricpoke->get_hp() <= 0){ // if after the hit electric poke lost its life
                        electricpoke->set_hp(0); // set its hp to 0 
                        break;
                    }
                }
            }else{ // if psychic has no power ups
                if(psychicpoke->is_terrain()){ // if terrain is psychic
                    electricpoke->set_hp(electricpoke->get_hp() - 2*(psychicpoke->get_damage()));// deals 2x damage
                    if(electricpoke->get_hp() <= 0){    // if after the hit electric poke lost its life
                        electricpoke->set_hp(0);    // set its hp to 0 
                        break;
                    }
                }else{
                    electricpoke->set_hp(electricpoke->get_hp() - psychicpoke->get_damage()); //deals 1x damage
                    if(electricpoke->get_hp() <= 0){// if after the hit electric poke lost its life
                        electricpoke->set_hp(0);// set its hp to 0 
                        break;
                    }
                }
            }
            //electric pokemons turn
            if(!electricpoke->is_fainted() || electricpoke->is_terrain()){  //if electric poke is not confused or it is in electric terrain cannot be confused
                if(electricpoke->is_powerup()){ //if electric poke has power up
                    psychicpoke->set_hp((psychicpoke->get_hp() - (electricpoke->get_damage() * 3))); //deals 3x damage
                    if(psychicpoke->get_hp() <= 0){  // if after the hit electric poke lost its life
                        psychicpoke->set_hp(0); // set its hp to 0
                        break;
                    }
                }else{ // if electric has no power up
                    psychicpoke->set_hp(psychicpoke->get_hp() - electricpoke->get_damage()); //deals 1x damage
                    if(psychicpoke->get_hp() <= 0){ // if after the hit electric poke lost its life
                        psychicpoke->set_hp(0); // set its hp to 0
                        break;
                    }
                }
            }else{ // if electric is confused so cannot attack
                counter_fa++; // increment confuse timer by 1
                if(electricpoke->is_powerup()) // check if it has power up but cannot attack because poke is confused
                    psychicpoke->set_hp(psychicpoke->get_hp()); // end the round
            }
        }else if(select == 1){ //fight starts with electric pokemon
            if(electricpoke->is_terrain() || psychicpoke->is_terrain())  // if terrain is elec or psy
                counter_ter++; // increase counter by 1
            if(!electricpoke->is_fainted() || electricpoke->is_terrain()){ //if electric poke is not confused or it is in electric terrain cannot be confused
                if(electricpoke->is_powerup()){ //if electric poke has power up
                    psychicpoke->set_hp((psychicpoke->get_hp() - (electricpoke->get_damage() * 3))); //deals 3x damage
                    if(psychicpoke->get_hp() <= 0){ // if after the hit electric poke lost its life
                        psychicpoke->set_hp(0);// set its hp to 0
                        break;
                    }
                }else{ // if electric has no power up
                    psychicpoke->set_hp(psychicpoke->get_hp() - (electricpoke->get_damage())); //deals 1x damage
                    if(psychicpoke->get_hp() <= 0){ // if after the hit electric poke lost its life
                        psychicpoke->set_hp(0); // set its hp to 0
                        break;
                    }
                }
            }else{ // if electric is confused so cannot attack
                counter_fa++; // increment confuse timer by 1
                if(electricpoke->is_powerup()) // check if it has power up but cannot attack because poke is confused
                    psychicpoke->set_hp(psychicpoke->get_hp()); // continue to round
                
            }
            //pyschic pokemons turn
            if(psychicpoke->is_powerup()){ // if psychic has power up
                if(psychicpoke->is_terrain()){ // if psychic is in its terrain
                    electricpoke->set_fainted(true); // electric poke is confused
                    electricpoke->set_hp(electricpoke->get_hp() - 2*(psychicpoke->get_damage())); // deals 2x damage to elec poke
                    if(electricpoke->get_hp() <= 0){ // if after the hit electric poke lost its life
                        electricpoke->set_hp(0); // set its hp to 0 
                        break;
                    }
                }else{ //if psychic is not in its terrain 
                    if(!electricpoke->is_terrain()) // if terrain is not electric
                        electricpoke->set_fainted(true); // electric poke will be confused 
                    electricpoke->set_hp((electricpoke->get_hp() - psychicpoke->get_damage())); // hit 1x damage to electric poke
                    if(electricpoke->get_hp() <= 0){ // if after the hit electric poke lost its life
                        electricpoke->set_hp(0); // set its hp to 0 
                        break;
                    }
                }
            }else{ // if psychic has no power ups
                if(psychicpoke->is_terrain()){ // if terrain is psychic
                    electricpoke->set_hp(electricpoke->get_hp() - 2*(psychicpoke->get_damage()));// deals 2x damage
                    if(electricpoke->get_hp() <= 0){    // if after the hit electric poke lost its life
                        electricpoke->set_hp(0);    // set its hp to 0 
                        break;
                    }
                }else{
                    electricpoke->set_hp(electricpoke->get_hp() - psychicpoke->get_damage()); //deals 1x damage
                    if(electricpoke->get_hp() <= 0){// if after the hit electric poke lost its life
                        electricpoke->set_hp(0);// set its hp to 0 
                        break;
                    }
                }
            }
        }
        printRoundStats(round, select); // print round stats at end of every round with the roun number and who starts first count
        round++; // increment round count
    }
    printRoundStats(round, final_select); // print last round when some pokemon has died :(
    printMatchResults(); // print the match results
    restartTerrain(); // reset the terrain when fight is over
    delete electricpoke; // delete allocated memory
    delete psychicpoke; // delete allocated memory
}

void Arena::spawnTerrain(){ // spawn new terrain
    int tran = rand() % 100 + 1; // create random number between 1-100
    if(tran < 21){ // if random is in first %20  terrain type is electric
        this->chosen_terrain = terrain_type[1]; // assign chosen terrain to selected terain
        electricpoke->set_terrain(true); // its electric pokemons terrain so set terrain true for electric pokemon
        psychicpoke->set_terrain(false); // not psy terrain
    }else if(tran < 41){
        this->chosen_terrain = terrain_type[2];
        electricpoke->set_terrain(false); // not elec terrain
        psychicpoke->set_terrain(true); // its psychic pokemons terrain so set terrain true for psychic pokemon
    }else{
        this->chosen_terrain = terrain_type[0]; // terrain type is None
        electricpoke->set_terrain(false); // not elec terrain
        psychicpoke->set_terrain(false); // not psy terrain
    }
}
void Arena::restartTerrain(){ // reset terrain type
    electricpoke->set_terrain(false);  // not elec terrain
    psychicpoke->set_terrain(false); // not psy terrain
    this->chosen_terrain = "reset"; // terrain type is reset
}

void Arena::printRoundStats(int round, int heads) const{ // print the round stats
    std::cout << "Round: " << round << std::endl;
    std::cout << "Current Terrain: " << chosen_terrain << std::endl;
    if(heads == 1){
        std::cout << electricpoke->get_name() << " goes first." << std::endl;
    }else if(heads == 0){
        std::cout << psychicpoke->get_name() << " goes first." << std::endl;
    }
    if(electricpoke->get_powerup())
        std::cout << electricpoke->get_name() << " has initiated a power up." << std::endl;
    if(psychicpoke->get_powerup())
        std::cout << psychicpoke->get_name() << " has initiated a power up." << std::endl;
    std::cout << electricpoke->get_name() << " HP:" << electricpoke->get_hp() << std::endl;
    std::cout << psychicpoke->get_name() << " HP:" << psychicpoke->get_hp() << std::endl;
    if(psychicpoke->get_hp() > electricpoke->get_hp()){
        std::cout << psychicpoke->get_name() << " is in the lead!" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    }else if(psychicpoke->get_hp() < electricpoke->get_hp()){
        std::cout << electricpoke->get_name() << " is in the lead!" << std::endl; 
        std::cout << std::endl;
        std::cout << std::endl;
    }else{
        std::cout << "No one is in the lead!" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl; 
    }
}

void Arena::printMatchResults() const{ // print the match results
    std::cout << "Match Results: " << std::endl;
    if(electricpoke->get_hp() == 0){
        std::cout << psychicpoke->get_name() << " has won the match!" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    }else if(psychicpoke->get_hp() == 0){
        std::cout << electricpoke->get_name() << " has won the match!" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    }else{
        return;
    }
}
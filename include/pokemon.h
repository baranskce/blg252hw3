/* @Author
* Student Name: Baran Işık
* Student ID : 150190087
*/

#include <iostream>
#pragma once

class Pokemon{
public:
    Pokemon(std::string, char, int,int);
    std::string get_name() const;
    int get_hp() const;
    void set_hp(int);
    int get_damage() const;
   

private:
    std::string pokename;
    const char type;
    const int damage;
    int hitpoints;
    
    
};
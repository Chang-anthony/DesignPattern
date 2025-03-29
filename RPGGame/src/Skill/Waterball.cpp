#include "Waterball.hpp"
#include <iostream>

Waterball::Waterball()
{
    setName("Waterball");
    setMp(50);
    setTargetEnemy(1);
    setTargetFriend(0);
}

void Waterball::attack(std::vector<Role*> roles)
{
    // TODO: Implement full attack algorithm for Waterball
    std::cout << "Waterball executed on target enemy with 50 MP." << std::endl;
}

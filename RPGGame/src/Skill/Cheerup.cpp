#include "Cheerup.hpp"
#include <iostream>

Cheerup::Cheerup()
{
    setName("Cheerup");
    setMp(100);
    setTargetEnemy(0); // No enemy targeted
    setTargetFriend(3); // Target 3 friends
}

void Cheerup::attack(std::vector<Role*> roles)
{
    // TODO: Implement full attack algorithm for Cheerup
    std::cout << "Cheerup executed on 3 allies with 100 MP." << std::endl;
}

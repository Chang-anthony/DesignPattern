#include "Curse.hpp"
#include <iostream>

Curse::Curse()
{
    setName("Curse");
    setMp(100);
    setTargetEnemy(1); // Target one enemy
    setTargetFriend(0); // No friend targeted
}

void Curse::attack(std::vector<Role*> roles)
{
    // TODO: Implement full attack algorithm for Curse
    std::cout << "Curse executed on one enemy with 100 MP." << std::endl;
}

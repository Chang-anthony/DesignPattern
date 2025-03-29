#include "Poison.hpp"
#include <iostream>

Poison::Poison()
{
    setName("Poison");
    setMp(80);
    setTargetEnemy(1);
    setTargetFriend(0);
}

void Poison::attack(std::vector<Role*> roles)
{
    // TODO: Implement full attack algorithm for Poison
    std::cout << "Poison executed on one enemy with 80 MP." << std::endl;
}

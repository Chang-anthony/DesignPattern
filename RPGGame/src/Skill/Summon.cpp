#include "Summon.hpp"
#include <iostream>

Summon::Summon()
{
    setName("Summon");
    setMp(150);
    setTargetEnemy(0); // No enemy targeted
    setTargetFriend(0); // No friend targeted
}

void Summon::attack(std::vector<Role*> roles)
{
    // TODO: Implement full attack algorithm for Summon
    std::cout << "Summon executed on all allies with 150 MP." << std::endl;
}

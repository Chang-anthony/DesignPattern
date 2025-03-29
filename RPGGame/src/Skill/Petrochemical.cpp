#include "Petrochemical.hpp"
#include <iostream>

Petrochemical::Petrochemical()
{
    setName("Petrochemical");
    setMp(100);
    setTargetEnemy(1);
    setTargetFriend(0);
}

void Petrochemical::attack(std::vector<Role*> roles)
{
    std::cout << "Petrochemical executed on one enemy with 100 MP." << std::endl;
}

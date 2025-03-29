#include "BasicAttack.hpp"
#include <iostream>

BasicAttack::BasicAttack()
{
    setName("BasicAttack");
    setMp(0);
    setTargetEnemy(1);
    setTargetFriend(0);
}

//TODO: Implement the attack method
void BasicAttack::attack(std::vector<Role*> roles)
{
    std::cout << "BasicAttack executed on target enemy." << std::endl;
}

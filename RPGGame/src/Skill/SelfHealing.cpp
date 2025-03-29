#include "SelfHealing.hpp"
#include <iostream>

SelfHealing::SelfHealing()
{
    setName("SelfHealing");
    setMp(50);
    setTargetEnemy(0); // No enemy targeted
    setTargetFriend(TARGET_FRIEND_SELF);
}

void SelfHealing::attack(std::vector<Role*> roles)
{
    std::cout << "SelfHealing executed on self with 50 MP." << std::endl;
}

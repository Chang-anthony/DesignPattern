#include "SelfExplosion.hpp"
#include <iostream>

SelfExplosion::SelfExplosion()
{
    setName("SelfExplosion");
    setMp(200);
    setTargetEnemy(TARGET_ENEMY_ALL); // Target all enemies
    setTargetFriend(TARGET_FRIEND_ALL); // Target all friends
}

void SelfExplosion::attack(std::vector<Role*> roles)
{
    // TODO: Implement full attack algorithm for SelfExplosion
    std::cout << "SelfExplosion executed on all enemies and allies with 200 MP." << std::endl;
}

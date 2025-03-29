#include "Fireball.hpp"
#include <iostream>

Fireball::Fireball()
{
    setName("Fireball");
    setMp(50);
    setTargetEnemy(TARGET_ENEMY_ALL);
    setTargetFriend(0);
}

void Fireball::attack(std::vector<Role*> roles)
{
    std::cout << "Fireball executed on all enemies with 50 MP." << std::endl;
}

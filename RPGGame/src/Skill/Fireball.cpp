#include "Fireball.hpp"
#include <iostream>
#include "Role.hpp"

Fireball::Fireball()  : Skill(){
    setName("Fireball");
    setMp(50);
    setTargetEnemy(TARGET_ENEMY_ALL);
    setTargetFriend(0);
}

void Fireball::attack(Role* actor, std::vector<Role*> targets) {
    for (auto target : targets) {
        target->damage(50); // Example damage value
    }
}

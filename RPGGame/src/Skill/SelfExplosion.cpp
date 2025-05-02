#include "SelfExplosion.hpp"
#include <iostream>
#include "Role.hpp"

SelfExplosion::SelfExplosion() : Skill() {
    setName("SelfExplosion");
    setMp(200);
    setTargetEnemy(TARGET_ENEMY_ALL);
    setTargetFriend(TARGET_FRIEND_ALL);
}

void SelfExplosion::attack(Role* actor, std::vector<Role*> targets) {
    for (auto target : targets) {
        /* code */
        target->damage(150);
    }
    actor->damage(actor->getHp()); // Actor self-damage
}

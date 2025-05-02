#include "SelfHealing.hpp"
#include <iostream>
#include "Role.hpp"

SelfHealing::SelfHealing() : Skill() {
    setName("SelfHealing");
    setMp(50);
    setTargetEnemy(0);
    setTargetFriend(TARGET_FRIEND_SELF);
}

void SelfHealing::attack(Role* actor, std::vector<Role*> targets) {
    actor->gainHp(150);
}

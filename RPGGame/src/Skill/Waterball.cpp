#include "Waterball.hpp"
#include <iostream>
#include "Role.hpp"

Waterball::Waterball() : Skill() {
    setName("Waterball");
    setMp(50);
    setTargetEnemy(1);
    setTargetFriend(0);
}

void Waterball::attack(Role* actor, std::vector<Role*> targets) {
    for (auto target : targets) {
        target->damage(120);
    }
}

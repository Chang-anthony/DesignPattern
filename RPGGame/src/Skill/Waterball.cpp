#include "Waterball.hpp"
#include <iostream>
#include "Role.hpp"
#include "State.hpp"

Waterball::Waterball() : Skill() {
    setName("水球");
    setMp(50);
}

void Waterball::attack(Role* actor, std::vector<Role*> targets) {
    for (auto target : targets) {
        actor->getState()->doDamage(target, 120);
    }
}

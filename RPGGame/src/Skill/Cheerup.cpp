#include "Cheerup.hpp"
#include <iostream>
#include "State.hpp"
#include "CheerupedState.hpp"
#include "Role.hpp"

Cheerup::Cheerup() : Skill() {
    setName("Cheerup");
    setMp(100);
    setTargetEnemy(0);
    setTargetFriend(3);
}

void Cheerup::attack(Role* actor, std::vector<Role*> targets) {
    for (auto target : targets) {
        target->setState(new CheerupedState());
    }
}

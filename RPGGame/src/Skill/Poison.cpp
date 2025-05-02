#include "Poison.hpp"
#include <iostream>
#include "Role.hpp"
#include "PoisonedState.hpp"

Poison::Poison()  : Skill() {
    setName("Poison");
    setMp(80);
    setTargetEnemy(1);
    setTargetFriend(0);
}

void Poison::attack(Role* actor, std::vector<Role*> targets) {

    for (auto target : targets) {  
        /* code */
        target->setState(new PoisonedState());
    }
}

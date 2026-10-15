#include "Poison.hpp"
#include <iostream>
#include "Role.hpp"
#include "PoisonedState.hpp"

Poison::Poison()  : Skill() {
    setName("下毒");
    setMp(80);
}

void Poison::attack(Role* actor, std::vector<Role*> targets) {

    for (auto target : targets) {  
        /* code */
        target->setState(new PoisonedState());
    }
}

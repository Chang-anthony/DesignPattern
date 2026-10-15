#include "Cheerup.hpp"
#include <iostream>
#include "State.hpp"
#include "CheerupedState.hpp"
#include "Role.hpp"

Cheerup::Cheerup() : Skill() {
    setName("鼓舞");
    setMp(100);
}

void Cheerup::attack(Role* actor, std::vector<Role*> targets) {
    for (auto target : targets) {
        target->setState(new CheerupedState());
    }
}

// 目標：3 位友軍（不含自己）
Candidates Cheerup::getCandidates(Role* actor, const std::vector<Role*>& t1,
                              const std::vector<Role*>& t2, int actorSide) const {
    return {alliesOf(actor, t1, t2, actorSide), 3};
}

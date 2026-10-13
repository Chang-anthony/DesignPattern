#include "Fireball.hpp"
#include <iostream>
#include "Role.hpp"
#include "State.hpp"

Fireball::Fireball()  : Skill(){
    setName("火球");
    setMp(50);
}

void Fireball::attack(Role* actor, std::vector<Role*> targets) {
    for (auto target : targets) {
        actor->getState()->doDamage(target, 50);
    }
}

// 目標：所有敵軍（m = n，自動全選）
Candidates Fireball::getCandidates(Role* actor, const std::vector<Role*>& t1,
                              const std::vector<Role*>& t2, int actorSide) const {
    std::vector<Role*> enemies = enemiesOf(t1, t2, actorSide);
    return {enemies, static_cast<int>(enemies.size())};
}

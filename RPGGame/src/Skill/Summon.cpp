#include "Summon.hpp"
#include <iostream>
#include "SkillObserver.hpp"
#include "Role.hpp"
#include "SummonObserver.hpp"
#include "Slime.hpp"
#include "Troop.hpp"

Summon::Summon()  : Skill() {
    setName("召喚");
    setMp(150);
}

void Summon::attack(Role* actor, std::vector<Role*> targets) {
    Troop* troop = actor->getTroop();
    Slime* slime = new Slime(100, 0, 50, "Slime");
    SummonObserver* observer = new SummonObserver(actor);
    slime->addObserver(observer);
    troop->addRole(slime);
}

// 目標：無（m = 0，略過 S2）
Candidates Summon::getCandidates(Role* actor, const std::vector<Role*>& t1,
                              const std::vector<Role*>& t2, int actorSide) const {
    return {{}, 0};
}

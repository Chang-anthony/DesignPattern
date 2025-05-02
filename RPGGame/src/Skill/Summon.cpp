#include "Summon.hpp"
#include <iostream>
#include "SkillObserver.hpp"
#include "Role.hpp"
#include "SummonObserver.hpp"
#include "Slime.hpp"
#include "Troop.hpp"

Summon::Summon()  : Skill() {
    setName("Summon");
    setMp(150);
    setTargetEnemy(0);
    setTargetFriend(0);
}

void Summon::attack(Role* actor, std::vector<Role*> targets) {
    Troop* troop = actor->getTroop();
    Slime* slime = new Slime(100, 0, 50, "Slime");
    SummonObserver* observer = new SummonObserver(actor);
    slime->addObserver(observer);
    troop->addRole(slime);
}

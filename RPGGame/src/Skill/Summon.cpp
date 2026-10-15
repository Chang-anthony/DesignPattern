#include "Summon.hpp"
#include <iostream>
#include "SkillObserver.hpp"
#include "Role.hpp"
#include "SummonObserver.hpp"
#include "Slime.hpp"
#include "Troop.hpp"
#include "AIAction.hpp"

Summon::Summon()  : Skill() {
    setName("召喚");
    setMp(150);
}

void Summon::attack(Role* actor, std::vector<Role*> targets) {
    Troop* troop = actor->getTroop();
    Slime* slime = new Slime(); // 史萊姆的數值由 Slime 自己持有（D44）
    SummonObserver* observer = new SummonObserver(actor);
    slime->addObserver(observer);
    slime->setDecider(new AIAction()); // 英雄以外的角色都由 AI 操控；史萊姆和其他角色一樣透過 setDecider 攜帶決策者（D4、D40）
    troop->addRole(slime);
}

// 目標：無（m = 0，略過 S2）
Candidates Summon::getCandidates(Role* actor, const std::vector<Role*>& t1,
                              const std::vector<Role*>& t2, int actorSide) const {
    return {{}, 0};
}

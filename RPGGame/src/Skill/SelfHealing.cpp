#include "SelfHealing.hpp"
#include <iostream>
#include "Role.hpp"

SelfHealing::SelfHealing() : Skill() {
    setName("自我治療");
    setMp(50);
}

void SelfHealing::attack(Role* actor, std::vector<Role*> targets) {
    actor->gainHp(150);
}

// 目標：自己
Candidates SelfHealing::getCandidates(Role* actor, const std::vector<Role*>& t1,
                              const std::vector<Role*>& t2, int actorSide) const {
    return {{actor}, 1};
}

// 「X 使用了 自我治療。」（自我治療不列出目標）
void SelfHealing::announce(Role* actor, const std::vector<Role*>& targets) const {
    std::cout << actor->getDisplayName() << " 使用了 " << getName() << "。" << std::endl;
}

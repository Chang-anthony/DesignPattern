#include "SelfExplosion.hpp"
#include <iostream>
#include "Role.hpp"
#include "State.hpp"

SelfExplosion::SelfExplosion() : Skill() {
    setName("自爆");
    setMp(200);
}

void SelfExplosion::attack(Role* actor, std::vector<Role*> targets) {
    for (auto target : targets) {
        actor->getState()->doDamage(target, 150);
    }
    // 自殺不在這裡做：它是自爆的 HP 代價（costHp），由 State::decision() 在施放之後支付（D47）
}

// 代價 = 施放者目前全部的 HP；流程支付時只印「<自己> 死亡。」，不印傷害訊息（D34）
int SelfExplosion::costHp(Role* actor) const {
    return actor->getHp();
}

// 目標：全場其他活著的角色，依 T1 → T2（不含自己，D34）
Candidates SelfExplosion::getCandidates(Role* actor, const std::vector<Role*>& t1,
                              const std::vector<Role*>& t2, int actorSide) const {
    std::vector<Role*> others = othersOf(actor, t1, t2);
    return {others, static_cast<int>(others.size())};
}

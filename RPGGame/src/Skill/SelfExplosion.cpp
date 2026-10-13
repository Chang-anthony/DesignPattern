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
    // 所有目標處理完後才自殺；不印傷害訊息，只由 lossHp() 印「<自己> 死亡。」（D34）
    actor->lossHp(actor->getHp()); // Actor self-damage
}

// 目標：全場其他活著的角色，依 T1 → T2（不含自己，D34）
Candidates SelfExplosion::getCandidates(Role* actor, const std::vector<Role*>& t1,
                              const std::vector<Role*>& t2, int actorSide) const {
    std::vector<Role*> others = othersOf(actor, t1, t2);
    return {others, static_cast<int>(others.size())};
}

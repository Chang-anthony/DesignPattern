#ifndef SELFEXPLOSION_HPP
#define SELFEXPLOSION_HPP

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class SelfExplosion : public Skill {
public:
    SelfExplosion();
    Candidates getCandidates(Role* actor, const std::vector<Role*>& t1,
                             const std::vector<Role*>& t2, int actorSide) const override;
    void attack(Role* actor, std::vector<Role*> targets) override;
    // 自殺是施放自爆的代價：全部 HP（D34、D47）
    int costHp(Role* actor) const override;
};

#endif // SELFEXPLOSION_HPP

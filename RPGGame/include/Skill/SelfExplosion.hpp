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
};

#endif // SELFEXPLOSION_HPP

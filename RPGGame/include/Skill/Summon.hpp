#ifndef SUMMON_HPP
#define SUMMON_HPP

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class Summon : public Skill {
public:
    Summon();
    Candidates getCandidates(Role* actor, const std::vector<Role*>& t1,
                             const std::vector<Role*>& t2, int actorSide) const override;
    void attack(Role* actor, std::vector<Role*> targets) override;
};

#endif // SUMMON_HPP

#ifndef SELFHEALING_HPP
#define SELFHEALING_HPP

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class SelfHealing : public Skill {
public:
    SelfHealing();
    Candidates getCandidates(Role* actor, const std::vector<Role*>& t1,
                             const std::vector<Role*>& t2, int actorSide) const override;
    void announce(Role* actor, const std::vector<Role*>& targets) const override;
    void attack(Role* actor, std::vector<Role*> targets) override;
};

#endif // SELFHEALING_HPP

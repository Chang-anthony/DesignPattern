#ifndef FIREBALL_HPP
#define FIREBALL_HPP

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class Fireball : public Skill {
public:
    Fireball();
    Candidates getCandidates(Role* actor, const std::vector<Role*>& t1,
                             const std::vector<Role*>& t2, int actorSide) const override;
    void attack(Role* actor, std::vector<Role*> targets) override;
};

#endif // FIREBALL_HPP

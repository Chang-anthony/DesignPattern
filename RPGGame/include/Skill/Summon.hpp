#ifndef SUMMON_HPP
#define SUMMON_HPP

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class Summon : public Skill {
public:
    Summon();
    void attack(Role* actor, std::vector<Role*> targets) override;
};

#endif // SUMMON_HPP

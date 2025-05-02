#ifndef POISON_HPP
#define POISON_HPP

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class Poison : public Skill {
public:
    Poison();
    void attack(Role* actor, std::vector<Role*> targets) override;
};

#endif // POISON_HPP

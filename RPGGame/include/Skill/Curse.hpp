#ifndef CURSE_HPP
#define CURSE_HPP

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class Curse : public Skill {
public:
    Curse();
    void attack(Role* actor, std::vector<Role*> targets) override;
};

#endif // CURSE_HPP

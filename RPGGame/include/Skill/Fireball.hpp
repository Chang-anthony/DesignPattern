#ifndef FIREBALL_HPP
#define FIREBALL_HPP

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class Fireball : public Skill {
public:
    Fireball();
    void attack(Role* actor, std::vector<Role*> targets) override;
};

#endif // FIREBALL_HPP

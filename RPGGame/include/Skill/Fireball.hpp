#ifndef FIREBALL_HPP
#define FIREBALL_HPP

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class Fireball : public Skill
{
public:
    Fireball();
    void attack(std::vector<Role*> roles) override;
};

#endif // FIREBALL_HPP

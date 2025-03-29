#ifndef POISON_HPP
#define POISON_HPP

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class Poison : public Skill
{
public:
    Poison();
    void attack(std::vector<Role*> roles) override;
};

#endif // POISON_HPP

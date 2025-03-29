#ifndef CURSE_HPP
#define CURSE_HPP

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class Curse : public Skill
{
public:
    Curse();
    void attack(std::vector<Role*> roles) override;
};

#endif // CURSE_HPP

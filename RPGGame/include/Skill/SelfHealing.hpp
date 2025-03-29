#ifndef SELFHEALING_HPP
#define SELFHEALING_HPP

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class SelfHealing : public Skill
{
public:
    SelfHealing();
    void attack(std::vector<Role*> roles) override;
};

#endif // SELFHEALING_HPP

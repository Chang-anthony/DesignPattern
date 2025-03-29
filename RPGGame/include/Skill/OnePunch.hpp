#ifndef ONEPUNCH_HPP
#define ONEPUNCH_HPP

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class OnePunch : public Skill
{
public:
    OnePunch();
    void attack(std::vector<Role*> roles) override;
};

#endif // ONEPUNCH_HPP

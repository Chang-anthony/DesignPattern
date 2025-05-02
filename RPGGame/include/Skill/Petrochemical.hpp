#ifndef PETROCHEMICAL_HPP
#define PETROCHEMICAL_HPP

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class Petrochemical : public Skill
{
public:
    Petrochemical();
    void attack(Role* actor, std::vector<Role*> roles) override;
};

#endif // PETROCHEMICAL_HPP

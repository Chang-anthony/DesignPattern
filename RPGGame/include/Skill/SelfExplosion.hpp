#ifndef SELFEXPLOSION_HPP
#define SELFEXPLOSION_HPP

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class SelfExplosion : public Skill
{
public:
    SelfExplosion();
    void attack(std::vector<Role*> roles) override;
};

#endif // SELFEXPLOSION_HPP

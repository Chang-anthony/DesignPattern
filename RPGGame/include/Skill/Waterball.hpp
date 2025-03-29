#ifndef WATERBALL_HPP
#define WATERBALL_HPP

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class Waterball : public Skill
{
public:
    Waterball();
    void attack(std::vector<Role*> roles) override;
};

#endif // WATERBALL_HPP

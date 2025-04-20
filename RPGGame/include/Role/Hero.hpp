#ifndef HERO_HPP
#define HERO_HPP

#include "Role.hpp"
#include <string>

class Hero : public Role {
public:
    Hero(int hp, int mp, int str, const std::string& name);
    Hero(int hp, int mp, int str, const std::string& name, const std::vector<Skill*>& skills);

    // No additional members; inherits everything from Role
};

#endif // HERO_HPP

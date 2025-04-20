#ifndef NONHERO_HPP
#define NONHERO_HPP

#include "Role.hpp"
#include <string>

class NonHero : public Role {
public:
    NonHero(int hp, int mp, int str, const std::string& name);

    // No additional members; inherits everything from Role except skills
};

#endif // NONHERO_HPP

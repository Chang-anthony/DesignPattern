#ifndef SLIME_HPP
#define SLIME_HPP

#include "NonHero.hpp"
#include <string>

class Slime : public NonHero {
public:
    Slime(int hp, int mp, int str, const std::string& name);

    // Additional methods or attributes specific to Slime can be added here
};

#endif // SLIME_HPP

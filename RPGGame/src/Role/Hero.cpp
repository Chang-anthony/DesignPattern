#include "Hero.hpp"

Hero::Hero(int hp, int mp, int str, const std::string& name)
    : Role(hp, mp, str, name) {}

Hero::Hero(int hp, int mp, int str, const std::string& name, const std::vector<Skill*>& skills)
    : Role(hp, mp, str, name, skills) {}



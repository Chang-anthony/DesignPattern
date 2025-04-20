#include "AI.hpp"

AI::AI(int hp, int mp, int str, const std::string& name, int seed)
    : Role(hp, mp, str, name), seed(seed) {}

AI::AI(int hp, int mp, int str, const std::string& name, const std::vector<Skill*>& skills, int seed)
    : Role(hp, mp, str, name, skills), seed(seed) {}

int AI::getSeed() const {
    return seed;
}

void AI::setSeed(int newSeed) {
    seed = newSeed;
}

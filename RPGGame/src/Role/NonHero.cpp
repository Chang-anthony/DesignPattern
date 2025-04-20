#include "NonHero.hpp"
#include "../State/NormalState.hpp"

NonHero::NonHero(int hp, int mp, int str, const std::string& name)
    : Role(hp, mp, str, name) {
    setState(new NormalState()); // Default state is NormalState
}

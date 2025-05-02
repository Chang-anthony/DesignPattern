#include "Petrochemical.hpp"
#include <iostream>
#include "Role.hpp"
#include "PetrochemicaledState.hpp"


Petrochemical::Petrochemical()
{
    setName("Petrochemical");
    setMp(100);
    setTargetEnemy(1);
    setTargetFriend(0);
}

void Petrochemical::attack(Role* actor, std::vector<Role*> targets)
{
    for (auto target : targets) {
        target->setState(new PetrochemicaledState());
    }
}

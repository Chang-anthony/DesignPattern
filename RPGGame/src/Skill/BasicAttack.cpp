#include "BasicAttack.hpp"
#include <iostream>
#include "Role.hpp"

BasicAttack::BasicAttack()
{
    setName("BasicAttack");
    setMp(0);
    setTargetEnemy(1);
    setTargetFriend(0);
}

void BasicAttack::attack(Role* actor, std::vector<Role*> targets) {
    for (auto role: targets) {
        role->damage(actor->getStr());
    }
}

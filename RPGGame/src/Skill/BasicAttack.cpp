#include "BasicAttack.hpp"
#include <iostream>
#include "Role.hpp"
#include "State.hpp"

BasicAttack::BasicAttack() : Skill()
{
    setName("普通攻擊");
    setMp(0);
}

void BasicAttack::attack(Role* actor, std::vector<Role*> targets) {
    for (auto role: targets) {
        actor->getState()->doDamage(role, actor->getStr());
    }
}

// 「X 攻擊 Y。」
void BasicAttack::announce(Role* actor, const std::vector<Role*>& targets) const {
    for (Role* target : targets) {
        std::cout << actor->getDisplayName() << " 攻擊 " << target->getDisplayName() << "。" << std::endl;
    }
}

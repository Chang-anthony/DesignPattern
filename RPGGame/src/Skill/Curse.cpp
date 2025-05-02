#include "Curse.hpp"
#include <iostream>
#include "Role.hpp"
#include <vector>
#include "CurserObserver.hpp"
#include "SkillObserver.hpp"

Curse::Curse() : Skill(){
    setName("Curse");
    setMp(100);
    setTargetEnemy(1);
    setTargetFriend(0);
}

void Curse::attack(Role* actor, std::vector<Role*> targets) {
    for (auto target : targets) {
        std::vector<SkillObserver*> observers = target->getObservers();
        bool flag = false;

        for (auto obs : observers) {
            Role* pastActor = obs->getRole();
            if (actor == pastActor) {
                flag = true;
                break;
            }
        }

        if (!flag) {
            target->addObserver(new CurserObserver(actor));
        }
    }
}

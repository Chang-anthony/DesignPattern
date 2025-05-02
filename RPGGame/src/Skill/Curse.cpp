#include "Curse.hpp"
#include <iostream>
#include "Role.hpp"
#include <vector>
#include "CurserObserver.hpp"
#include "SkillObserver.hpp"

Curse::Curse() {
    setName("Curse");
    setMp(100);
    setTargetEnemy(1);
    setTargetFriend(0);
}

void Curse::attack(Role* actor, std::vector<Role*> targets) {

    for (auto target : targets) {
        std::vector<SkillObserver*> observers = target->getObservers();
        for (auto obs : observers) {
            Role* actor = obs->getRole();
            if (actor != actor) {
                //check the observer have this actor
                CurserObserver* observer = new CurserObserver(actor);
                target->addObserver(observer);
            }
        }
    }
}

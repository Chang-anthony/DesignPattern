#include "CurserObserver.hpp"
#include <iostream>
#include "Role.hpp"

CurserObserver::CurserObserver(Role* actor) : SkillObserver(actor) {

}


// 受詛咒者死亡且施咒者仍活著 → 施咒者 HP + 受詛咒者剩餘的 MP
void CurserObserver::UntilDie(Role* dead) {
    if (!actor->isDead()) {
        actor->gainHp(dead->getMp());
    }
}

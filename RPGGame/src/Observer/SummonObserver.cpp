#include "SummonObserver.hpp"
#include <iostream>
#include "Role.hpp"

SummonObserver::SummonObserver(Role* actor) : SkillObserver(actor) {

}


// 史萊姆死亡且召喚者仍活著 → 召喚者 HP + 30
void SummonObserver::UntilDie(Role* dead) {
    if (!actor->isDead()) {
        actor->gainHp(30);
    }
}

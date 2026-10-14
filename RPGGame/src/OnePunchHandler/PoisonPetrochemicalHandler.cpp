#include "PoisonPetrochemicalHandler.hpp"
#include "Role.hpp"
#include "State.hpp"
#include "PoisonedState.hpp"
#include "PetrochemicaledState.hpp"

PoisonPetrochemicalHandler::PoisonPetrochemicalHandler() {}

PoisonPetrochemicalHandler::~PoisonPetrochemicalHandler() {}

bool PoisonPetrochemicalHandler::match(Role* actor, Role* target) {

    return dynamic_cast<PoisonedState*>(target->getState()) != nullptr ||
           dynamic_cast<PetrochemicaledState*>(target->getState()) != nullptr;
}

void PoisonPetrochemicalHandler::doHandle(Role* actor, Role* target) {
    // 目標死亡後剩下的幾下不再出手（testcases/one-punch.out：第 2 下死亡 → 沒有第 3 行傷害；§7.2 I4）
    for (size_t i = 0; i < 3 && !target->isDead(); i++) {
        actor->getState()->doDamage(target, 80);
    }
}

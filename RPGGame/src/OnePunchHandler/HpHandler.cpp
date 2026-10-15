#include "HpHandler.hpp"
#include "Role.hpp"
#include "State.hpp"

HpHandler::HpHandler(){}

HpHandler::~HpHandler() {}

bool HpHandler::match(Role* actor, Role* target) {
    return target->getHp() >= 500;
}

void HpHandler::doHandle(Role* actor, Role* target) {
    actor->getState()->doDamage(target, 300);
}

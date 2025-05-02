#include "HpHandler.hpp"
#include "Role.hpp"

HpHandler::HpHandler(){}

HpHandler::HpHandler(OnePunchHandler* nextHandler)
    : OnePunchHandler(nextHandler) { }

HpHandler::~HpHandler() {}

bool HpHandler::match(Role* target) {
    return target->getHp() >= 500;
}

void HpHandler::doHandle(Role* target) {
    target->damage(300);
}

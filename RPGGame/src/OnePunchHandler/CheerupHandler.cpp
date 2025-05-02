#include "CheerupHandler.hpp"
#include "Role.hpp"
#include "State.hpp"
#include "NormalState.hpp"

CheerupHandler::CheerupHandler() {}

CheerupHandler::CheerupHandler(OnePunchHandler* nextHandler)
    : OnePunchHandler(nextHandler) {}

CheerupHandler::~CheerupHandler() {}

bool CheerupHandler::match(Role* target) {
    return target->getState()->getName() == "CheerupedState";
}

void CheerupHandler::doHandle(Role* target) {
    target->damage(100);
    target->setState(new NormalState());
}

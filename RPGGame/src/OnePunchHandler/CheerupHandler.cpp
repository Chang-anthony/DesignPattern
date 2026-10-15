#include "CheerupHandler.hpp"
#include "Role.hpp"
#include "State.hpp"
#include "NormalState.hpp"
#include "CheerupedState.hpp"

CheerupHandler::CheerupHandler() {}

CheerupHandler::~CheerupHandler() {}

bool CheerupHandler::match(Role* actor, Role* target) {
    return dynamic_cast<CheerupedState*>(target->getState()) != nullptr;
}

void CheerupHandler::doHandle(Role* actor, Role* target) {
    actor->getState()->doDamage(target, 100);
    target->setState(new NormalState());
}

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
    for (size_t i = 0; i < 3; i++) {
        actor->getState()->doDamage(target, 80);
    }
}

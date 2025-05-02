#include "PoisonPetrochemicalHandler.hpp"
#include "Role.hpp"
#include "State.hpp"

PoisonPetrochemicalHandler::PoisonPetrochemicalHandler() {}

PoisonPetrochemicalHandler::PoisonPetrochemicalHandler(OnePunchHandler* nextHandler)
    : OnePunchHandler(nextHandler) {}

PoisonPetrochemicalHandler::~PoisonPetrochemicalHandler() {}

bool PoisonPetrochemicalHandler::match(Role* target) {

    return target->getState()->getName() == "PoisonedState" ||
           target->getState()->getName() == "PetrochemicaledState";
}

void PoisonPetrochemicalHandler::doHandle(Role* target) {
    for (size_t i = 0; i < 3; i++) {
        target->damage(80);
    }
}

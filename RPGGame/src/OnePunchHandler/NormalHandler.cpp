#include "NormalHandler.hpp"
#include "Role.hpp"
#include "State.hpp"
#include "NormalState.hpp"

NormalHandler::NormalHandler() {}

NormalHandler::~NormalHandler() {}

bool NormalHandler::match(Role* actor, Role* target) {
    // Logic to determine if this handler should handle the request

    return dynamic_cast<NormalState*>(target->getState()) != nullptr;
}

void NormalHandler::doHandle(Role* actor, Role* target) {
    actor->getState()->doDamage(target, 100);
}

#include "NormalHandler.hpp"
#include "Role.hpp"
#include "State.hpp"

NormalHandler::NormalHandler() {}

NormalHandler::NormalHandler(OnePunchHandler* nextHandler) : OnePunchHandler(nextHandler) {}

NormalHandler::~NormalHandler() {}

//TODO:
bool NormalHandler::match(Role* target) {
    // Logic to determine if this handler should handle the request

    return target->getState()->getName() == "NormalState";
}

void NormalHandler::doHandle(Role* target) {
    target->damage(100);
}

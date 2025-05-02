#include "OnePunchHandler.hpp"
#include "utils.h"
#include "Role.hpp"

OnePunchHandler::OnePunchHandler() : next(nullptr) {}

OnePunchHandler::OnePunchHandler(OnePunchHandler* nextHandler) {
    setNext(nextHandler);
}

OnePunchHandler::~OnePunchHandler() {}

void OnePunchHandler::setNext(OnePunchHandler* nextHandler) {
    utils::RequireNonNull(nextHandler);
    next = nextHandler;
}

OnePunchHandler* OnePunchHandler::getNext() const {
    return next;
}


void OnePunchHandler::handle(Role* target) {
    if (match(target)) {
        doHandle(target);
    } else if (next) {
        next->handle(target);
    }
}

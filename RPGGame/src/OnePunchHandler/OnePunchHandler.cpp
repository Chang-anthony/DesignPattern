#include "OnePunchHandler.hpp"
#include "utils/utils.h"

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


//TODO: need implementation this two function 
void OnePunchHandler::handle() {
    if (match()) {
        doHandle();
    } else if (next) {
        next->handle();
    }
}

bool OnePunchHandler::match() const {
    return true; // Default implementation, can be overridden by derived classes
}

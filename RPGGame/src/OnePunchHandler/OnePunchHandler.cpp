#include "OnePunchHandler.hpp"
#include "utils.h"
#include "Role.hpp"

OnePunchHandler::OnePunchHandler() {}

OnePunchHandler::~OnePunchHandler() {}

bool OnePunchHandler::handle(Role* actor, Role* target) {
    if (match(actor, target)) {
        doHandle(actor, target);
        return true;
    }
    return false;
}

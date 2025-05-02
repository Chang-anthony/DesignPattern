#include "SkillObserver.hpp"
#include "../Role/Role.hpp"
#include <utils.h>

SkillObserver::SkillObserver(Role* actor) {
    setRole(actor);
}

void SkillObserver::setRole(Role* associatedRole) {
    utils::RequireNonNull(associatedRole);
    actor = associatedRole;
}

Role* SkillObserver::getRole() {
    return actor;
}

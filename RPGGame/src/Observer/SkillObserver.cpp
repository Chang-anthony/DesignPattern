#include "SkillObserver.hpp"
#include "../Role/Role.hpp"
#include <utils.h>

SkillObserver::SkillObserver(Role* associatedRole) {
    setRole(associatedRole);
}

void SkillObserver::setRole(Role* associatedRole) {
    utils::RequireNonNull(associatedRole);
    role = associatedRole;
}

Role* SkillObserver::getRole() const {
    return role;
}

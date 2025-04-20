#include "Troop.hpp"
#include "Battle.hpp"
#include "Role.hpp"
#include <iostream>
#include "../utils/utils.h"

Troop::Troop() {}

Troop::~Troop() {}

void Troop::addRole(Role* role) {
    utils::RequireNonNull(role);
    roles.emplace_back(role);
}

bool Troop::Annihilated() const {
    for (const auto& role : roles) {
        if (!role->isDead()) {
            return false; // If any role is not dead, the troop is not annihilated
        }
    }
    return true; // All roles are dead
}

Battle* Troop::StartBattle(Troop* enemy) {
    utils::RequireNonNull(enemy);
    return new Battle(this, enemy);
} 


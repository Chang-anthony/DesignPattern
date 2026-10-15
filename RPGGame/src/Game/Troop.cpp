#include "Troop.hpp"
#include "Role.hpp"
#include <iostream>
#include "utils.h"

Troop::Troop() : id(1) {}

Troop::Troop(int id) : id(id) {}

int Troop::getId() const {
    return id;
}

Troop::~Troop() {
    for (Role* role : roles) {
        delete role; // Troop 擁有角色（D49）
    }
}

void Troop::addRole(Role* role) {
    utils::RequireNonNull(role);
    roles.emplace_back(role);
    role->setTroop(this); // Set the troop for the role
}


std::vector<Role*> Troop::getRoles() const {
    return roles;
}

void Troop::removeRole(Role* role) {
    utils::RequireNonNull(role);
    roles = utils::RemoveObjectFromVector(roles, role);
    role->setTroop(nullptr); // Clear the troop reference in the role
}


bool Troop::Annihilated() const {
    for (const auto& role : roles) {
        if (!role->isDead()) {
            return false; // If any role is not dead, the troop is not annihilated
        }
    }
    return true; // All roles are dead
}

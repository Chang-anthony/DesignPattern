#include "State.hpp"
#include <iostream>
#include "utils.h"
#include "Role.hpp"

State::State() : round(0), role(nullptr), name("") {} // Default constructor

State::State(Role* role) :
    round(0), role(utils::RequireNonNull(role)), name("State") {} // Constructor with Role parameter

State::~State() {}

int State::getRound() const {
    return round;
}

void State::setRound(int round) {
    this->round = round;
}

Role* State::getRole() const {
    return role;
}

void State::setRole(Role* role) {
    utils::RequireNonNull(role);
    this->role = role;
}

std::string State::getName() const {
    return name;
}

void State::entryState(State* newState) {
    utils::RequireNonNull(newState);
}

void State::exitState() {
}

void State::doDamage(Role* target, int n) {
    utils::RequireNonNull(target);
    std::cout << utils::RequireNonNull(role)->getDisplayName() << " 對 " << target->getDisplayName()
              << " 造成 " << n << " 點傷害。" << std::endl;
    utils::RequireNonNull(target->getState())->damage(n);
}

void State::damage(int n) {
    utils::RequireNonNull(role)->lossHp(n);
}

// TODO: Implement the decision method in derived classes
// No implementation for decision() as it is a pure virtual function.

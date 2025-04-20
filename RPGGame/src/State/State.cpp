#include "State.hpp"
#include <iostream>
#include "utils.h"

State::State() : round(0), role(nullptr) {} // Default constructor

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

void State::entryState(State* newState) {
    utils::RequireNonNull(newState);
    std::cout << "Entering state with " << round << " rounds." << std::endl;
}

void State::exitState() {
    std::cout << "Exiting state with " << round << " rounds." << std::endl;
}

// TODO: Implement the decision method in derived classes
// No implementation for decision() as it is a pure virtual function.

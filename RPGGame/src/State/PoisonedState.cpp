#include "PoisonedState.hpp"

PoisonedState::PoisonedState() : State() {
    name = "PoisonedState";
}

PoisonedState::~PoisonedState() {}

// TODO: implement the decision method
void PoisonedState::decision() {
    std::cout << "PoisonedState: Making a decision while poisoned." << std::endl;
}

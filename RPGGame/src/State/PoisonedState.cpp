#include "PoisonedState.hpp"

PoisonedState::PoisonedState() : State() {}

PoisonedState::~PoisonedState() {}

// TODO: implement the decision method
void PoisonedState::decision() {
    std::cout << "PoisonedState: Making a decision while poisoned." << std::endl;
}

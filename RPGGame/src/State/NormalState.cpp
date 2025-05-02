#include "NormalState.hpp"

NormalState::NormalState() : State() {
    name = "NormalState";
}

NormalState::~NormalState() {}

// TODO: implement the decision method
void NormalState::decision() {
    std::cout << "NormalState: Making a decision." << std::endl;
}

#include "CheerupedState.hpp"

CheerupedState::CheerupedState() : State() {
    name = "CheerupedState";
}

CheerupedState::~CheerupedState() {}

//TODO: implement the decision method
void CheerupedState::decision() {
    std::cout << "CheerupedState: Making a decision while in a cheer-up state." << std::endl;
}

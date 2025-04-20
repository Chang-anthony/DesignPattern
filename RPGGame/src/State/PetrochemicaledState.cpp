#include "PetrochemicaledState.hpp"

PetrochemicaledState::PetrochemicaledState() : State() {}

PetrochemicaledState::~PetrochemicaledState() {}

// TODO: implement the decision method
void PetrochemicaledState::decision() {
    std::cout << "PetrochemicaledState: Unable to make a decision due to being petrified." << std::endl;
}

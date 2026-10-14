#include "NormalState.hpp"

NormalState::NormalState() : State() {
    name = "NormalState";
}

NormalState::~NormalState() {}

// TODO: implement the decision method
void NormalState::decision(const std::vector<Role*>& t1, const std::vector<Role*>& t2, int actorSide) {
    std::cout << "NormalState: Making a decision." << std::endl;
}

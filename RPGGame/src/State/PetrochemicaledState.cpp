#include "PetrochemicaledState.hpp"

PetrochemicaledState::PetrochemicaledState() : State() {
    name = "PetrochemicaledState";
    setRound(3); // 3 回合（含當前回合）；被新狀態覆寫時重新計算（D11）
}

PetrochemicaledState::~PetrochemicaledState() {}

// TODO: implement the decision method
void PetrochemicaledState::decision() {
    std::cout << "PetrochemicaledState: Unable to make a decision due to being petrified." << std::endl;
}

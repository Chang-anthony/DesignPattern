#include "PoisonedState.hpp"

PoisonedState::PoisonedState() : State() {
    name = "PoisonedState";
    setRound(3); // 3 回合（含當前回合）；被新狀態覆寫時重新計算（D11）
}

PoisonedState::~PoisonedState() {}

// TODO: implement the decision method
void PoisonedState::decision(const std::vector<Role*>& t1, const std::vector<Role*>& t2, int actorSide) {
    std::cout << "PoisonedState: Making a decision while poisoned." << std::endl;
}

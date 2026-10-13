#include "CheerupedState.hpp"

CheerupedState::CheerupedState() : State() {
    name = "CheerupedState";
    setRound(3); // 3 回合（含當前回合）；被新狀態覆寫時重新計算（D11）
}

CheerupedState::~CheerupedState() {}

//TODO: implement the decision method
void CheerupedState::decision() {
    std::cout << "CheerupedState: Making a decision while in a cheer-up state." << std::endl;
}

void CheerupedState::doDamage(Role* target, int n) {
    State::doDamage(target, n + 50);
}

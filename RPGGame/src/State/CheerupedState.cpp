#include "CheerupedState.hpp"

CheerupedState::CheerupedState() : State() {
    name = "CheerupedState";
    displayName = "受到鼓舞";
    setRound(3); // 3 回合（含當前回合）；被新狀態覆寫時重新計算（D11）
}

CheerupedState::~CheerupedState() {}

void CheerupedState::doDamage(Role* target, int n) {
    State::doDamage(target, n + 50);
}

#include "PetrochemicaledState.hpp"

PetrochemicaledState::PetrochemicaledState() : State() {
    name = "PetrochemicaledState";
    displayName = "石化";
    setRound(3); // 3 回合（含當前回合）；被新狀態覆寫時重新計算（D11）
}

PetrochemicaledState::~PetrochemicaledState() {}

// 石化：這一輪不行動，也不問決策者（AI 的 seed 不變、英雄不讀輸入）
void PetrochemicaledState::decision(const std::vector<Role*>& t1, const std::vector<Role*>& t2, int actorSide) {
}

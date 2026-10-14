#include "PoisonedState.hpp"
#include "Role.hpp"
#include "utils.h"

PoisonedState::PoisonedState() : State() {
    name = "PoisonedState";
    displayName = "中毒";
    setRound(3); // 3 回合（含當前回合）；被新狀態覆寫時重新計算（D11）
}

PoisonedState::~PoisonedState() {}

void PoisonedState::decision(const std::vector<Role*>& t1, const std::vector<Role*>& t2, int actorSide) {
    Role* actor = utils::RequireNonNull(getRole());
    actor->lossHp(30); // 走 lossHp：歸零時印「死亡。」並通知觀察者（D17）；不印傷害訊息
    if (actor->isDead()) {
        return;
    }
    State::decision(t1, t2, actorSide);
}

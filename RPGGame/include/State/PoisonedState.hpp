#ifndef _POISONEDSTATE_H_
#define _POISONEDSTATE_H_

#include "State.hpp"
#include <iostream>

class PoisonedState : public State {
public:
    PoisonedState(); // Default constructor
    ~PoisonedState();

    // 中毒：進入 S1 前 HP − 30；因此死亡就不能行動，否則沿用 State::decision() 的預設流程
    void decision(const std::vector<Role*>& t1, const std::vector<Role*>& t2, int actorSide) override;
};

#endif /* _POISONEDSTATE_H_ */

#ifndef NORMALSTATE_HPP
#define NORMALSTATE_HPP

#include "State.hpp"
#include <iostream>

class NormalState : public State {
public:
    NormalState(); // Default constructor
    ~NormalState();
    // 正常狀態：沿用 State::decision() 的預設流程
};

#endif // NORMALSTATE_HPP

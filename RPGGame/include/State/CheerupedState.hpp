#ifndef CHEERUPEDSTATE_HPP
#define CHEERUPEDSTATE_HPP

#include "State.hpp"
#include <iostream>

class CheerupedState : public State {
public:
    CheerupedState(); // Default constructor
    ~CheerupedState();
    // 行動流程沿用 State::decision()；只改變造成傷害的方式

    // 受到鼓舞：每次造成傷害額外 +50（D13、D15、D16）
    void doDamage(Role* target, int n) override;
};

#endif // CHEERUPEDSTATE_HPP

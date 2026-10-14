#ifndef CHEERUPEDSTATE_HPP
#define CHEERUPEDSTATE_HPP

#include "State.hpp"
#include <iostream>

class CheerupedState : public State {
public:
    CheerupedState(); // Default constructor
    ~CheerupedState();

    void decision(const std::vector<Role*>& t1, const std::vector<Role*>& t2, int actorSide) override;

    // 受到鼓舞：每次造成傷害額外 +50（D13、D15、D16）
    void doDamage(Role* target, int n) override;
};

#endif // CHEERUPEDSTATE_HPP

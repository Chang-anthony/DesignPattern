#ifndef PETROCHEMICALEDSTATE_HPP
#define PETROCHEMICALEDSTATE_HPP

#include "State.hpp"
#include <iostream>

class PetrochemicaledState : public State {
public:
    PetrochemicaledState(); // Default constructor
    ~PetrochemicaledState();

    // 石化：S1、S2、S3 全部略過（「輪到 …」那一行由 Role::takeTurn 印，仍會印出）
    void decision(const std::vector<Role*>& t1, const std::vector<Role*>& t2, int actorSide) override;
};

#endif // PETROCHEMICALEDSTATE_HPP

#ifndef NORMALSTATE_HPP
#define NORMALSTATE_HPP

#include "State.hpp"
#include <iostream>

class NormalState : public State {
public:
    NormalState(); // Default constructor
    ~NormalState();

    void decision(const std::vector<Role*>& t1, const std::vector<Role*>& t2, int actorSide) override;
};

#endif // NORMALSTATE_HPP

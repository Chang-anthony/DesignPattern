#ifndef NORMALSTATE_HPP
#define NORMALSTATE_HPP

#include "State.hpp"
#include <iostream>

class NormalState : public State {
public:
    NormalState(); // Default constructor
    ~NormalState();

    void decision() override;
};

#endif // NORMALSTATE_HPP

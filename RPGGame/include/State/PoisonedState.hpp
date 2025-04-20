#ifndef POISONEDSTATE_HPP
#define POISONEDSTATE_HPP

#include "State.hpp"
#include <iostream>

class PoisonedState : public State {
public:
    PoisonedState(); // Default constructor
    ~PoisonedState();

    void decision() override;
};

#endif // POISONEDSTATE_HPP

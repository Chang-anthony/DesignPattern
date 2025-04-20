#ifndef CHEERUPEDSTATE_HPP
#define CHEERUPEDSTATE_HPP

#include "State.hpp"
#include <iostream>

class CheerupedState : public State {
public:
    CheerupedState(); // Default constructor
    ~CheerupedState();

    void decision() override;
};

#endif // CHEERUPEDSTATE_HPP

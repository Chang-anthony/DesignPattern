#ifndef PETROCHEMICALEDSTATE_HPP
#define PETROCHEMICALEDSTATE_HPP

#include "State.hpp"
#include <iostream>

class PetrochemicaledState : public State {
public:
    PetrochemicaledState(); // Default constructor
    ~PetrochemicaledState();

    void decision() override;
};

#endif // PETROCHEMICALEDSTATE_HPP

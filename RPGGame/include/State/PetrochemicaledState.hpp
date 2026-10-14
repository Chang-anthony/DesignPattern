#ifndef PETROCHEMICALEDSTATE_HPP
#define PETROCHEMICALEDSTATE_HPP

#include "State.hpp"
#include <iostream>

class PetrochemicaledState : public State {
public:
    PetrochemicaledState(); // Default constructor
    ~PetrochemicaledState();

    void decision(const std::vector<Role*>& t1, const std::vector<Role*>& t2, int actorSide) override;
};

#endif // PETROCHEMICALEDSTATE_HPP

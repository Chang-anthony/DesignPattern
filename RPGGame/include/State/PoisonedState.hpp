#ifndef _POISONEDSTATE_H_
#define _POISONEDSTATE_H_

#include "State.hpp"
#include <iostream>

class PoisonedState : public State {
public:
    PoisonedState(); // Default constructor
    ~PoisonedState();

    void decision() override;
};

#endif /* _POISONEDSTATE_H_ */

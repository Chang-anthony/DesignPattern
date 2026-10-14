#ifndef _POISONEDSTATE_H_
#define _POISONEDSTATE_H_

#include "State.hpp"
#include <iostream>

class PoisonedState : public State {
public:
    PoisonedState(); // Default constructor
    ~PoisonedState();

    void decision(const std::vector<Role*>& t1, const std::vector<Role*>& t2, int actorSide) override;
};

#endif /* _POISONEDSTATE_H_ */

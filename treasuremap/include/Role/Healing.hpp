#ifndef _HEALING_H_
#define _HEALING_H_

#include <iostream>
#include "State.hpp"

class Role;

class Healing : public State
{
private:
    /* data */
public:
    Healing(Role* role);
    ~Healing();

    void enterState() override;
    void exitState(State* nextState) override;
    void action() override;
    void attacked(int damage) override;
    std::string StateName() override;

    friend class Role;
};

#endif /* _HEALING_H_ */

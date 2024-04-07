#ifndef _TELEPORT_H_
#define _TELEPORT_H_

#include <iostream>
#include "State.hpp"

class Role;

class Teleport : public State
{
private:
    /* data */
public:
    Teleport(Role* role);
    ~Teleport();

    void enterState() override;
    void exitState(State* nextState) override;
    void action() override;
    void attacked(int damage) override;
    std::string StateName() override;
    void test() override;

    friend class Role;
};

#endif /* _TELEPORT_H_ */

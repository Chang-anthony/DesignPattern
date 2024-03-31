#ifndef _ERUPTING_H_
#define _ERUPTING_H_

#include <iostream>
#include "State.hpp"

class Role;

class Erupting : public State
{
private:
    /* data */
public:
    Erupting(Role* role);
    ~Erupting();

    void enterState() override;
    void exitState(State* nextState) override;
    void action() override;
    void attacked(int damage) override;
    std::string StateName() override;

    friend class Role;
};

#endif /* _ERUPTING_H_ */

#ifndef _NORMALSTATE_H_
#define _NORMALSTATE_H_

#include <iostream>
#include "State.hpp"

class Role;

class NormalState : public State
{
private:
    /* data */
public:
    NormalState(Role* role);
    ~NormalState();

    void enterState() override;
    void exitState() override;
    void action() override;
    void attacked(int damage) override;
    std::string StateName() override;

    friend class Role;
};

#endif /* _NORMALSTATE_H_ */

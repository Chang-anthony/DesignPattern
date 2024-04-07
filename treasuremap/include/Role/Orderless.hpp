#ifndef _ORDERLESS_H_
#define _ORDERLESS_H_

#include <iostream>
#include "State.hpp"

class Role;

class Orderless : public State
{
private:
    /* data */
    void randomMove();
public:
    Orderless(Role* role);
    ~Orderless();

    void enterState() override;
    void exitState(State* nextState) override;
    void action() override;
    void attacked(int damage) override;
    std::string StateName() override;
    void test() override;
};


#endif /* _ORDERLESS_H_ */

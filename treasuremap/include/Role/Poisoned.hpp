#ifndef _POISONED_H_
#define _POISONED_H_

#include <iostream>
#include <State.hpp>

class Role;

class Poisoned : public State
{
private:
    /* data */
public:
    Poisoned(Role* role);
    ~Poisoned();

    void enterState() override;
    void exitState(State* nextState) override;
    void action() override;
    void attacked(int damage) override;
    std::string StateName() override;
    void test() override;

    friend class Role;
};

#endif /* _POISONED_H_ */

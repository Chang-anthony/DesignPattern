#ifndef _ACCELERATED_H_
#define _ACCELERATED_H_

#include <iostream>
#include <State.hpp>

class Role;

class Accelerated : public State
{
private:
    /* data */
public:
    Accelerated(Role* role);
    ~Accelerated();

    void enterState() override;
    void exitState(State* nextState) override;
    void action() override;
    void attacked(int damage) override;
    std::string StateName() override;

    friend class Role;
};

#endif /* _ACCELERATED_H_ */

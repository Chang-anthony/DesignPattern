#ifndef _STOCKPILE_H_
#define _STOCKPILE_H_

#include <iostream>
#include "State.hpp"

class Role;

class Stockpile : public State
{
private:
    /* data */
public:
    Stockpile(Role* role);
    ~Stockpile();

    void enterState() override;
    void exitState(State* nextState) override;
    void action() override;
    void attacked(int damage) override;
    std::string StateName() override;

    friend class Role;
};

#endif /* _STOCKPILE_H_ */

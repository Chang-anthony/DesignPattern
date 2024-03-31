#ifndef _STATE_H_
#define _STATE_H_

#include <iostream>
#include <string>

class Role;

class State
{
private:
public:
    State(Role* role);
    ~State();

    
protected:
    int round;
    Role* role;
    //function
    virtual void enterState() = 0;
    virtual void exitState(State* nextState) = 0;
    virtual void action() = 0;
    virtual void attacked(int damage) = 0;
    virtual std::string StateName() = 0;


    void SetRound(int round);
    void SetRole(Role* role);
    friend class Role;
};

#endif /* _STATE_H_ */

#ifndef _STATE_H_
#define _STATE_H_

#include <iostream>
#include <string>

class Role;

class State
{
private:
    int round;
    Role* role;
public:
    State(int round, Role* role);
    ~State();

    
protected:
    //function
    virtual void enterState() = 0;
    virtual void exitState() = 0;
    virtual void action() = 0;
    virtual void attacked(int damage) = 0;
    virtual std::string StateName() = 0;

    int GetRound();
    Role* GetRole();

    void SetRound(int round);
    void SetRole(Role* role);
    friend class Role;
};

#endif /* _STATE_H_ */

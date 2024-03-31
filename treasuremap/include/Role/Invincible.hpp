#ifndef _INVINCIBLE_H_
#define _INVINCIBLE_H_

#include <iostream>
#include <State.hpp>

class Role;

class Invincible : public State
{
private:
    /* data */
public:
    Invincible(Role* role);
    ~Invincible();

    void enterState() override;
    void exitState() override;
    void action() override;
    void attacked(int damage) override;
    std::string StateName() override;

    friend class Role;
};

#endif /* _INVINCIBLE_H_ */

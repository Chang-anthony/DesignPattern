#ifndef _FULLATTACK_H_
#define _FULLATTACK_H_

#include <iostream>
#include "AttackType.hpp"

class Role;

class FullAttack : public AttackType
{
private:
    /* data */
public:
    FullAttack(Role* role);
    ~FullAttack();
protected:
    void attack() override;
};

#endif /* _FULLATTACK_H_ */

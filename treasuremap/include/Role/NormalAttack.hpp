#ifndef _NORMALATTACK_H_
#define _NORMALATTACK_H_

#include <iostream>
#include "AttackType.hpp"

class Role;

class NormalAttack : public AttackType
{
private:
    /* data */
public:
    NormalAttack(Role* role);
    ~NormalAttack();
protected:
    void attack() override;
};


#endif /* _NORMALATTACK_H_ */

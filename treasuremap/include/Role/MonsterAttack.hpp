#ifndef _MONSTERATTACK_H_
#define _MONSTERATTACK_H_

#include <iostream>
#include "AttackType.hpp"

class Role;

class MonsterAttack : public AttackType
{
private:
    /* data */
public:
    MonsterAttack(Role* role);
    ~MonsterAttack();
protected:
    void attack() override;
};


#endif /* _MONSTERATTACK_H_ */

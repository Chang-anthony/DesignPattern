#ifndef _ATTACKTYPE_H_
#define _ATTACKTYPE_H_

#include <iostream>
class Role;

class AttackType
{
private:
    /* data */
public:
    AttackType(Role* charator);
    ~AttackType();

    //getter
    int GetDamage();
    Role* GetRole();

    //setter
    void SetDamage(int damage);
    void SetRole(Role* charator);

protected:
    int damage;
    Role* charator;
    virtual void attack() = 0;
    
    friend class Role;
};

#endif /* _ATTACKTYPE_H_ */

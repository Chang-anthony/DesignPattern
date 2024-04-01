#ifndef _CHARATOR_H_
#define _CHARATOR_H_

#include <iostream>
#include "Role.hpp"

class Coord;
class Adventure;
class AttackType;

class Charator : public Role
{
private:
    /* data */
public:
    Charator(Coord* pos, Adventure* game);
    ~Charator();

    void Do() override;
    bool fullHp() override;
    void gainHp(int Hp) override;

protected:
};


#endif /* _CHARATOR_H_ */

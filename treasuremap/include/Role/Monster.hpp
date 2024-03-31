#ifndef _MONSTER_H_
#define _MONSTER_H_

#include <iostream>
#include "Role.hpp"

class Adventure;
class Coord;

class Monster : public Role
{
private:
    /* data */
public:
    Monster(Coord* pos, Adventure* game);
    ~Monster();

    //TODO
    void Do() override;
    void injured(int damage) override;
    void attack() override;
};

#endif /* _MONSTER_H_ */

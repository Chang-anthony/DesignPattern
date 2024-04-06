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

    void Do() override;
    bool fullHp() override;
    void gainHp(int Hp) override;
    bool orderless(int random) override;

    static Monster* genMonster(Coord* newPos, Adventure* game);
};

#endif /* _MONSTER_H_ */

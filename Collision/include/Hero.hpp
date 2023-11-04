#ifndef _HERO_H_
#define _HERO_H_

#include "../include/Sprite.hpp"

class Hero : public Sprite
{
private:
    /* data */
    int hp;
public:
    Hero(/* args */);
    ~Hero();
    void GainHp(int hp);
    bool IsDead();

    //getter
    int GetHp();
};

#endif /* _HERO_H_ */

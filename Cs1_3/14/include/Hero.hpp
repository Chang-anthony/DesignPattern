#ifndef _HERO_H_
#define _HERO_H_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>

class Hero
{
private:
    /* data */
    int hp;
    int strength;
    int Defense;
    std::vector<Hero*> heros;
public:
    Hero();
    ~Hero();

    //
    void TakeTurn();
    void Attack(Hero* target);
    void SetHeros(std::vector<Hero*> heros);
};


#endif /* _HERO_H_ */

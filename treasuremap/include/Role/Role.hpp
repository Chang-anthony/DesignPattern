#ifndef _ROLE_H_
#define _ROLE_H_

#include <iostream>
#include <Mapobject.hpp>

class State;
class Coord;
class Adventure;

class Role : public Mapobject
{
private:
    /* data */
public:
    Role(char symbol, Coord* pos, Adventure* game);
    ~Role();

    //TODO
    //function
    void lossHp(int damage);
    void action();

    //override from mapobject
    void move(int x, int y) override;

    int GetHp();
    void SetHp(int hp);

    State* GetState();
    void EnterState(State* state);
protected:
    int Hp;
    State* state;

    bool isDead();
    virtual void Do() = 0;
    virtual void attack() = 0;
    virtual void gainHp(int Hp);
    virtual bool fullHp();
    void injured(int damage);

    friend class State;
    friend class NormalState;
    friend class Invincible;
    friend class Accelerated;
    friend class Poisoned;
    friend class Healing;
    friend class Stockpile;
    friend class Erupting;
    friend class Teleport;
    friend class Orderless;
};

#endif /* _ROLE_H_ */

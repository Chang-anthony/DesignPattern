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
    int Hp;
    State* state;

public:
    Role(char symbol, Coord* pos, Adventure* game);
    ~Role();

    //TODO
    //function
    bool fullHp();
    void lossHp(int damage);
    void action();

    //override from mapobject
    void move(int x, int y) override;

    int GetHp();
    void SetHp(int hp);

    State* GetState();
    void EnterState(State* state);
protected:
    bool isDead();
    virtual void Do() = 0;
    void injured(int damage);
    virtual void attack() = 0;

    friend class State;
    friend class NormalState;
    friend class Invincible;
};

#endif /* _ROLE_H_ */

#ifndef _ROLE_H_
#define _ROLE_H_

#include <iostream>
#include <Mapobject.hpp>

class State;
class Coord;
class Adventure;
class AttackType;

class Role : public Mapobject
{
private:
    /* data */
public:
    Role(std::string symbol, Coord* pos, Adventure* game);
    ~Role();

    //TODO
    //function
    void lossHp(int damage);
    void action();

    //override from mapobject
    void injured(int damage);
    void move(int x, int y) override;

    int GetHp();
    void SetHp(int hp);

    State* GetState();
    void EnterState(State* state);

    AttackType* GetAttackType();
    void SetAttackType(AttackType* type);
protected:
    int Hp;
    State* state;
    AttackType* attackType;

    bool isDead();
    virtual void Do() = 0;
    void attack();
    virtual void gainHp(int Hp) = 0;
    virtual bool fullHp() = 0;

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
    friend class AttackType;
};

#endif /* _ROLE_H_ */

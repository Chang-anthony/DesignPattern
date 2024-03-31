#include <Poisoned.hpp>
#include <Adventure.hpp>
#include <Invincible.hpp>
#include <NormalState.hpp>
#include <Role.hpp>

Poisoned::Poisoned(Role* role) : State(role)
{
}

void Poisoned::enterState()
{
    return;
}

void Poisoned::exitState(State* nextState)
{
    role->EnterState(nextState);
}

void Poisoned::action()
{
    //中毒效果
    role->lossHp(15);
    role->Do();
    round++;

    if(round > 3)
        exitState(new NormalState(role));
}

void Poisoned::attacked(int damage)
{
    role->lossHp(damage);
    if(!role->isDead())
        exitState(new Invincible(role));
}

std::string Poisoned::StateName()
{
    return "中毒";
}

Poisoned::~Poisoned()
{
}
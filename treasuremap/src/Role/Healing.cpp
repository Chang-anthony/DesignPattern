#include <Healing.hpp>
#include <NormalState.hpp>
#include <Invincible.hpp>
#include <Role.hpp>

Healing::Healing(Role* role) : State(role)
{
}

void Healing::enterState()
{
    return;
}

void Healing::exitState(State* nextState)
{
    role->EnterState(nextState);
}

void Healing::action()
{
    role->gainHp(30);
    role->Do();
    round++;
    if(round > 5 or role->fullHp())
        exitState(new NormalState(role));
}

void Healing::attacked(int damage)
{
    role->lossHp(damage);
    if(!role->isDead())
        exitState(new Invincible(role));
}

std::string Healing::StateName()
{
    return "回復";
}

Healing::~Healing()
{
}


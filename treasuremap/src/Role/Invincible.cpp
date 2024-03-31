#include <Invincible.hpp>
#include <Role.hpp>
#include <NormalState.hpp>

Invincible::Invincible(Role* role) : State(role)
{
}

void Invincible::enterState()
{
    return;
}

void Invincible::exitState(State* nextState)
{
    role->EnterState(nextState);
}

void Invincible::action()
{
    role->Do();
    SetRound(round + 1);
    if(round > 2)
        exitState(new NormalState(role));
}

void Invincible::attacked(int damage)
{
    role->lossHp(0);
}

std::string Invincible::StateName()
{
    return "無敵";
}

Invincible::~Invincible()
{
}
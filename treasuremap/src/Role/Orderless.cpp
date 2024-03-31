#include <Role.hpp>
#include <Invincible.hpp>
#include <NormalState.hpp>
#include <Orderless.hpp>

//TODO: randomMove
Orderless::Orderless(Role* role) : State(role)
{
}

void Orderless::enterState()
{
    return;
}

void Orderless::exitState(State* nextState)
{
    role->EnterState(nextState);
}

void Orderless::action()
{
    randomMove();
    round++;
    if(round > 3)
        exitState(new NormalState(role));
}

void Orderless::attacked(int damage)
{
    role->lossHp(damage);
    if(!role->isDead())
        exitState(new Invincible(role));
}

std::string Orderless::StateName()
{
    return "混亂";
}

Orderless::~Orderless()
{
}
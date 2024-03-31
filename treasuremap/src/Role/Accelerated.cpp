
#include <Role.hpp>
#include <NormalState.hpp>
#include <Adventure.hpp>
#include <Accelerated.hpp>

Accelerated::Accelerated(Role* role) : State(role)
{
}

void Accelerated::enterState()
{
    return;
}

void Accelerated::exitState(State* nextState)
{
    role->EnterState(nextState);
}

void Accelerated::action()
{
    for (int i = 0; i < 2; i++) {
        role->Do();
    }
    round++;
    if(round > 3)
        exitState(new NormalState(role));
}

void Accelerated::attacked(int damage)
{
    role->lossHp(damage);
    if(!role->isDead())
        exitState(new NormalState(role));
}

std::string Accelerated::StateName()
{
    return "加速";
}

Accelerated::~Accelerated()
{
}
#include <Role.hpp>
#include <NormalState.hpp>
#include <Invincible.hpp>
#include <Adventure.hpp>
#include <Erupting.hpp>
#include <Teleport.hpp>

//TODO
Erupting::Erupting(Role* role) : State(role)
{
}

void Erupting::enterState()
{
    //attacktype to full
}

void Erupting::exitState(State* nextState)
{
    role->EnterState(nextState);
}

void Erupting::action()
{
    role->Do();
    round++;

    if(round > 3)
        exitState(new Teleport(role));
}

void Erupting::attacked(int damage)
{
    role->lossHp(damage);
    if(!role->isDead())
        exitState(new Invincible(role));
}

std::string Erupting::StateName()
{
    return "爆發";
}

Erupting::~Erupting()
{
}

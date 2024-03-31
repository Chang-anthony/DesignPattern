#include <Role.hpp>
#include <NormalState.hpp>
#include <Invincible.hpp>
#include <Stockpile.hpp>
#include <Erupting.hpp>

Stockpile::Stockpile(Role* role) : State(role)
{
}

void Stockpile::enterState()
{
    return;
}

void Stockpile::exitState(State* state)
{
    role->Do();
}

void Stockpile::action()
{
    role->Do();
    round++;
    if(round > 2)
        exitState(new Erupting(role));
}

void Stockpile::attacked(int damage)
{
    role->lossHp(damage);
    if(!role->isDead())
        exitState(new NormalState(role));
}

std::string Stockpile::StateName()
{
    return "蓄力";
}

Stockpile::~Stockpile()
{
}
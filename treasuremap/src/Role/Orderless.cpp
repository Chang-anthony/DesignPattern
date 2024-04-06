#include <Role.hpp>
#include <Invincible.hpp>
#include <NormalState.hpp>
#include <Orderless.hpp>
#include <random>


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

//TODO: randomMove
void Orderless::randomMove()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    int random_number = dis(gen);
    role->orderless(random_number);
}

std::string Orderless::StateName()
{
    return "混亂";
}

Orderless::~Orderless()
{
}
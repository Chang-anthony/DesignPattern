#include <Role.hpp>
#include <NormalState.hpp>
#include <Adventure.hpp>
#include <Invincible.hpp>

NormalState::NormalState(Role* role) : State(role)
{
}

void NormalState::enterState()
{
    return;
}

void NormalState::exitState(State* nextState)
{
    return;
}

void NormalState::action()
{
    role->Do();
}

void NormalState::attacked(int damage)
{
    role->lossHp(damage);
    //to 無敵狀態
    if(!role->isDead())
        exitState(new Invincible(role));
}

std::string NormalState::StateName()
{
    return "正常";
}

NormalState::~NormalState()
{
}
#include <Role.hpp>
#include <NormalState.hpp>
#include <Adventure.hpp>
#include <Invincible.hpp>

NormalState::NormalState(Role* role) : State(0, role)
{
}

void NormalState::enterState()
{
    return;
}

void NormalState::exitState()
{
    return;
}

void NormalState::action()
{
    this->GetRole()->Do();
}

void NormalState::attacked(int damage)
{
    this->GetRole()->lossHp(damage);
    //to 無敵狀態
    this->GetRole()->EnterState(new Invincible(this->GetRole()));
}

std::string NormalState::StateName()
{
    return "正常";
}

NormalState::~NormalState()
{
}
#include <Invincible.hpp>
#include <Role.hpp>
#include <NormalState.hpp>

Invincible::Invincible(Role* role) : State(0, role)
{
}

void Invincible::enterState()
{
    return;
}

void Invincible::exitState()
{
    this->GetRole()->EnterState(new NormalState(this->GetRole()));
}

void Invincible::action()
{
    this->GetRole()->Do();
    this->SetRound(this->GetRound() + 1);
    if(this->GetRound() >= 2)
        this->exitState();
}

void Invincible::attacked(int damage)
{
    this->GetRole()->lossHp(0);
}

std::string Invincible::StateName()
{
    return "無敵";
}

Invincible::~Invincible()
{
}
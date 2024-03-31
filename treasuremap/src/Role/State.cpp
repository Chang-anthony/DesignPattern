#include <State.hpp>
#include <Role.hpp>
#include <utils.h>

State::State(int round, Role* role)
{
    SetRole(role);
    SetRound(0);
}

int State::GetRound()
{
    return this->round;
}

void State::SetRound(int round)
{
    this->round = round;
}

Role* State::GetRole()
{
    return this->role;
}

void State::SetRole(Role* role)
{
    this->role = utils::RequireNonNull(role);
}

State::~State()
{
}
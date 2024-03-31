#include <State.hpp>
#include <Role.hpp>
#include <utils.h>

State::State(Role* role)
{
    SetRole(role);
    SetRound(0);
}

void State::SetRound(int round)
{
    this->round = round;
}

void State::SetRole(Role* role)
{
    this->role = utils::RequireNonNull(role);
}

State::~State()
{
}
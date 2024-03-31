#include <Role.hpp>
#include <Adventure.hpp>
#include <Coord.hpp>
#include <utils.h>
#include <State.hpp>
#include <NormalState.hpp>

Role::Role(char symbol, Coord* pos, Adventure* game): Mapobject(symbol, pos, game)
{
    this->Hp = 0;
    this->state = new NormalState(this);
}

//角色的行動模式
void Role::action()
{
    this->state->action();
}

void Role::lossHp(int damage)
{
    this->SetHp(this->GetHp() - damage);
    if(isDead()) {
        this->GetGame()->remove(this);
    }
}

void Role::injured(int damage)
{
    this->state->attacked(damage);
}

bool Role::isDead()
{
    return this->GetHp() <= 0;
}

void Role::move(int x, int y)
{
    this->SetCoord(this->GetCoord()->GetX() + x, this->GetCoord()->GetY() + y);
}

bool Role::fullHp()
{
    return this->Hp > 0;
}

int Role::GetHp()
{
    return this->Hp;
}

State* Role::GetState()
{
    return this->state;
}

void Role::SetHp(int hp)
{
    utils::ValShouldBigger(hp, 0);
    this->Hp = hp;
}

void Role::EnterState(State * state)
{
    utils::RequireNonNull(state);
    if(this->state) {
        this->state->exitState();
    }
    this->state = state;
    this->state->enterState();
}

Role::~Role()
{
}
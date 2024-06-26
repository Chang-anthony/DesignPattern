#include <Role.hpp>
#include <Adventure.hpp>
#include <Coord.hpp>
#include <utils.h>
#include <State.hpp>
#include <NormalState.hpp>
#include <AttackType.hpp>

Role::Role(std::string symbol, Coord* pos, Adventure* game): Mapobject(symbol, pos, game)
{
    this->Hp = 0;
    this->state = new NormalState(this);
}

//角色的行動模式
void Role::action()
{
    this->state->action();
    // TODO: have easy to change to test function pattern?
    // this->state->test();
}

void Role::test()
{
    this->state->test();
}

void Role::lossHp(int damage)
{
    this->SetHp(this->GetHp() - damage);
    if(isDead()) {
        game->remove(this);
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
    std::vector<std::vector<Mapobject*>> objs = game->GetObjs();
    Coord* newPos = new Coord(this->GetCoord()->GetX() + x, this->GetCoord()->GetY() + y);
    if(game->IsNullObj(newPos)) {
        game->refersh(this, newPos);
    }
    else {
        Mapobject* obj2 = game->GetObjs()[newPos->GetX()][newPos->GetY()];
        game->touched(this, obj2);
    }
}

void Role::attack()
{
    attackType->attack();
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
    this->Hp = hp;
}

void Role::EnterState(State * state)
{
    utils::RequireNonNull(state);
    this->state = state;
    this->state->enterState();
}

AttackType* Role::GetAttackType()
{
    return this->attackType;
}

void Role::SetAttackType(AttackType* type)
{
    attackType = utils::RequireNonNull(type);
}

Role::~Role()
{
}
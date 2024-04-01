#include <Monster.hpp>
#include <Adventure.hpp>
#include <Coord.hpp>
#include <State.hpp>
#include <MonsterAttack.hpp>

Monster::Monster(Coord* pos, Adventure* game) : Role('M', pos, game)
{
    this->SetHp(1);
    SetAttackType(new MonsterAttack(this));
}
//TODO
void Monster::Do()
{
}

bool Monster::fullHp()
{
    return Hp >= 1;
}

void Monster::gainHp(int Hp)
{
    this->Hp += Hp;
    if(this->Hp > 1)
        this->Hp = 1;
}

Monster::~Monster()
{
}
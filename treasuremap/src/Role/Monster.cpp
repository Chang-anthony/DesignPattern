#include <Monster.hpp>
#include <Adventure.hpp>
#include <Coord.hpp>
#include <State.hpp>

Monster::Monster(Coord* pos, Adventure* game) : Role('M', pos, game)
{
    this->SetHp(1);
}

//TODO
void Monster::Do()
{
}

//攻擊
void Monster::attack()
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
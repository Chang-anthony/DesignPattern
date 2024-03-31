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


Monster::~Monster()
{
}
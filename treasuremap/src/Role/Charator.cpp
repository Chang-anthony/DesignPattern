#include <Charator.hpp>
#include <Adventure.hpp>
#include <Coord.hpp>
#include <NormalAttack.hpp>

Charator::Charator(Coord* pos, Adventure* game) : Role('↑', pos, game)
{
    SetHp(300);
    SetAttackType(new NormalAttack(this));
}

//TODO
void Charator::Do()
{
}

bool Charator::fullHp()
{
    return Hp >= 300;
}

void Charator::gainHp(int Hp)
{
    this->Hp += Hp;
    if(this->Hp >= 300)
        this->Hp = 300;
}

Charator::~Charator()
{
}
#include "../include/Hero.hpp"

Hero::Hero(/* args */):Sprite('H')
{
    //initial hp 30
    this->hp = 30;
}

void Hero::GainHp(int hp)
{
    this->hp += hp;
}

bool Hero::IsDead()
{
    return this->hp <= 0;
}

int Hero::GetHp()
{
    return this->hp;
}

Hero::~Hero()
{
}
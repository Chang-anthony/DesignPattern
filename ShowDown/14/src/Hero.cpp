#include "../include/Hero.hpp"


Hero::Hero(/* args */)
{
    hp = rand() % 100;
    strength = rand() % 20;
    Defense = rand() % 10;
    heros = std::vector<Hero*>();
}

void Hero::TakeTurn()
{
    for(auto hero:heros)
    {
        //選擇英雄要解偶
        Hero* target = heros[rand() % 4];
        if(hero != target)
            hero->Attack(target);
        else
            continue;
    }
}

void Hero::Attack(Hero* target)
{
    target->hp = target->hp - this->strength + target->Defense;
}


void Hero::SetHeros(std::vector<Hero*> heros)
{
    this->heros = heros;
}


Hero::~Hero()
{

}

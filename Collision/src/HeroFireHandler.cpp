#include "../include/HeroFireHandler.hpp"
#include "../include/Sprite.hpp"
#include "../include/Hero.hpp"
#include <typeinfo>
#include <iostream>

HeroFireHandler::HeroFireHandler(CollisionHandle* next)
                                    :CollisionHandle(next)
{
}

bool HeroFireHandler::match(Sprite* c1,Sprite* c2)
{
    return c1->GetType() == 'H' && c2->GetType() == 'F';
}

void HeroFireHandler::dohandle(Sprite* c1,Sprite* c2,Sprite** sprites)
{
    Hero* T = dynamic_cast<Hero*>(c1);
    T->GainHp(-10);
    if(T->GetHp() <= 0)
    {
        sprites[T->GetCoord()] = nullptr;
        sprites[c2->GetCoord()] = nullptr;
    }
    else
    {
        int coord2 = c2->GetCoord();
        sprites[c1->GetCoord()] = nullptr;
        T->SetCoord(coord2);
        sprites[coord2] = T;
    }
}

HeroFireHandler::~HeroFireHandler()
{
}
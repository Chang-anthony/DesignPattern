#include "../include/HeroWaterHandler.hpp"
#include "../include/Sprite.hpp"
#include "../include/Hero.hpp"
#include <typeinfo>
#include <iostream>

HeroWaterHandler::HeroWaterHandler(CollisionHandle* next)
                                :CollisionHandle(next)
{
}

bool HeroWaterHandler::match(Sprite* c1,Sprite* c2)
{
    return c1->GetType() == 'H' && c2->GetType() == 'W';
}

void HeroWaterHandler::dohandle(Sprite* c1,Sprite* c2,Sprite** sprites)
{
    // 使用 dynamic_cast 進行類型檢查和安全類型轉換
    Hero* T = dynamic_cast<Hero*>(c1);
    T->GainHp(10);
    int coord2 = c2->GetCoord();
    sprites[c1->GetCoord()] = nullptr;
    T->SetCoord(coord2);
    sprites[coord2] = T;
}
HeroWaterHandler::~HeroWaterHandler()
{
}
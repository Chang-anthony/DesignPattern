#include "../include/HeroWaterHandler.hpp"
#include "../include/Sprite.hpp"

HeroWaterHandler::HeroWaterHandler(CollisionHandle* next)
                                :CollisionHandle(next)
{
}

bool HeroWaterHandler::match(Sprite* c1,Sprite* c2)
{
    return c1->GetType() == 'H' && c2->GetType() == 'W';
}

void HeroWaterHandler::dohandle(Sprite* c1,Sprite* c2)
{
    
}

HeroWaterHandler::~HeroWaterHandler()
{
}
#include "../include/HeroFireHandler.hpp"
#include "../include/Sprite.hpp"

HeroFireHandler::HeroFireHandler(CollisionHandle* next)
                                    :CollisionHandle(next)
{
}

bool HeroFireHandler::match(Sprite* c1,Sprite* c2)
{
    return c1->GetType() == 'H' && c2->GetType() == 'F';
}

void HeroFireHandler::dohandle(Sprite* c1,Sprite* c2)
{
    
}

HeroFireHandler::~HeroFireHandler()
{
}
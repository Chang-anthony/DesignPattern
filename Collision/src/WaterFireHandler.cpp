#include "../include/WaterFireHandler.hpp"
#include "../include/Sprite.hpp"

WaterFireHandler::WaterFireHandler(CollisionHandle* next)
                            :CollisionHandle(next)
{
}

bool WaterFireHandler::match(Sprite* c1,Sprite* c2)
{
    return c1->GetType() == 'W' && c2->GetType() == 'F';
}

void WaterFireHandler::dohandle(Sprite* c1,Sprite* c2,Sprite** sprites)
{
    sprites[c1->GetCoord()] = nullptr;
    sprites[c2->GetCoord()] = nullptr;
}

WaterFireHandler::~WaterFireHandler()
{
}
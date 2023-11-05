#include "../include/SameTypeHandler.hpp"
#include "../include/Sprite.hpp"

SameTypeHandler::SameTypeHandler(CollisionHandle* next)
                                :CollisionHandle(next)
{
}

bool SameTypeHandler::match(Sprite* c1,Sprite* c2)
{
    return c1->GetType() == c2->GetType() ;
}

void SameTypeHandler::dohandle(Sprite* c1,Sprite* c2,Sprite** sprites)
{
    return;
}

SameTypeHandler::~SameTypeHandler()
{
}
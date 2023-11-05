#include "../include/CollisionHandle.hpp"
#include "../include/Sprite.hpp"

CollisionHandle::CollisionHandle(CollisionHandle* next):next(next)
{
}

void CollisionHandle::handle(Sprite* c1,Sprite* c2,Sprite** sprites)
{
    if(this->match(c1,c2))
    {
        this->dohandle(c1,c2,sprites);
    }
    else
    {
        this->next->handle(c1,c2,sprites);
    }
}

void CollisionHandle::SetNext(CollisionHandle* next)
{
    this->next = next;
}

CollisionHandle::~CollisionHandle()
{
    delete this;
}
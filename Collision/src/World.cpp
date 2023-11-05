#include "../include/World.hpp"
#include "../include/utils/utils.h"
#include "../include/Sprite.hpp"
#include "../include/CollisionHandle.hpp"


World::World()
{
    //this->CoR = CoR;

    this->SetSprites(this->GenSprites());
    
}

void World::AddSprite(Sprite* sprite)
{

    if(!this->sprites[sprite->GetCoord()])
    {
        this->sprites[sprite->GetCoord()] = sprite;
    }
}

void World::Move(int x1,int x2)
{

}

void World::Collision(Sprite* c1,Sprite* c2)
{
    //this->CoR->handle(c1,c2);
}

Sprite** World::GetSprites()
{
    return this->sprites;
}

Sprite* (*World::TestGenSprites())[30]
{
    Sprite* sprites[30];
    
    for (size_t i = 0; i < 30; i++)
    {
        sprites[i] = nullptr;
    }
    
    int count = 0;
    while(count < 10)
    {
        Sprite* sprite = Sprite::RandGenSprite();
        if(!sprites[sprite->GetCoord()])
        {
            sprites[sprite->GetCoord()] = sprite;
            count++;
        }
    }

    Sprite* (*out)[30] = &sprites;

    return out;
}

void World::SetSprites(Sprite** sprites)
{
    for (size_t i = 0; i < 30; i++)
    {
        this->sprites[i] = sprites[i];
    }
}

void World::SetSprites(Sprite* (*sprites)[30])
{
    for (size_t i = 0; i < 30; i++)
    {
        this->sprites[i] = (*sprites)[i];
    }
    
}

Sprite** World::GenSprites()
{
    Sprite* sprites[30];
    
    for (size_t i = 0; i < 30; i++)
    {
        sprites[i] = nullptr;
    }
    
    int count = 0;
    while(count < 10)
    {
        Sprite* sprite = Sprite::RandGenSprite();
        if(!sprites[sprite->GetCoord()])
        {
            sprites[sprite->GetCoord()] = sprite;
            count++;
        }
    }

    //out is pointer to array have 30 pointer sprites*[30] 
    //*out is &sprites[0]
    //**out is Sprites() val or *(out[0])
    Sprite** out = sprites;

    return out;
}


World::~World()
{
    delete this;
}
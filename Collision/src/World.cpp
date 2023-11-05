#include "../include/World.hpp"
#include "../include/utils/utils.h"
#include "../include/Sprite.hpp"


World::World(/* args */)
{
    this->sprites = std::vector<Sprite*>();

    while(this->sprites.size() < 10)
    {
        Sprite* sprite = Sprite::RandGenSprite();
        if(this->position.find(sprite->GetCoord()) == this->position.end())
        {
            this->position.insert(sprite->GetCoord());
            this->sprites.push_back(sprite);
        }
    }

}

std::vector<Sprite*> World::GetSprites()
{
    return this->sprites;
}

std::set<int> World::GetPostion()
{
    return this->position;
}

void World::SetSprites(std::vector<Sprite*> sprites)
{
    this->sprites = sprites;
}

World::~World()
{

}
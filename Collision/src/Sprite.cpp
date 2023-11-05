#include "../include/Sprite.hpp"
#include "../include/utils/utils.h"
#include "../include/Hero.hpp"
#include "../include/Water.hpp"
#include "../include/Fire.hpp"
#include <random>


Sprite::Sprite(char type)
{
    this->coord = std::rand() % 30;
    utils::ValShouldBe(this->coord,0,29);
    this->SetType(type);
}

void Sprite::Remove()
{
    this->~Sprite();
}

Sprite* Sprite::RandGenSprite()
{
    std::vector<Sprite*> sprites = std::vector<Sprite*>{
                            new Water(),
                            new Fire(),
                            new Hero()
                            };
    
    return sprites[std::rand() % sprites.size()];
}

int Sprite::GetCoord()
{
    return this->coord;
}

char Sprite::GetType()
{
    return this->type;
}

void Sprite::SetCoord(int coord)
{
    this->coord = coord;
    utils::ValShouldBe(this->coord,0,29);
}

void Sprite::SetType(char type)
{
    this->type = type;
}

Sprite::~Sprite()
{
    //delete this;
}


#include "../include/Sprite.hpp"
#include "../include/utils/utils.h"
#include <random>


Sprite::Sprite(char type)
{
    this->coord = std::rand() % 30;
    utils::ValShouldBe(this->coord,0,29);
    this->SetType(type);
}

Sprite::~Sprite()
{
    delete this;
}

void Sprite::Remove()
{
    this->~Sprite();
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
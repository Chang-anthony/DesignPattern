#include "../include/Water.hpp"

Water::Water(/* args */):Sprite('W')
{
}

void Water::Remove()
{
    this->~Water();
}

Water::~Water()
{
    delete this;
}
#include "../include/Fire.hpp"

Fire::Fire(/* args */):Sprite('F')
{
}

void Fire::Remove()
{
    this->~Fire();
}

Fire::~Fire()
{
    delete this;
}



#include "../include/Challenge.h"

Challenge::Challenge(int id,std::string name)
{
    SetID(id);
    SetName(name);
};

int Challenge::GetID()
{
    return this->id;
}

std::string Challenge::GetName()
{
    return this->name;
}

void Challenge::SetID(int id)
{
    utils::ValShouldBigger(id,0);
    this->id = id;
}

void Challenge::SetName(std::string name)
{
    utils::LengthShouldBe(name,1,30);
    this->name = name;
}

Challenge::~Challenge()
{
}
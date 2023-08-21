#include "../include/Chapter.h"
#include "../include/Mission.h"

Chapter::Chapter(int id,std::string name,std::vector<Mission*> missions)
{
    SetID(id);
    SetName(name);
    SetMissions(missions);
};

int Chapter::GetID()
{
    return this->id;
}

std::string Chapter::GetName()
{
    return this->name;
}

std::vector<Mission*> Chapter::GetMissions()
{
    return this->missions;
}

void Chapter::SetID(int id)
{
    utils::ValShouldBigger(id,0);
    this->id = id;
}

void Chapter::SetName(std::string name)
{
    utils::LengthShouldBe(name,1,30);
    this->name = name;
}

void Chapter::SetMissions(std::vector<Mission*> missions)
{
    utils::SizeShouldBigger(missions,0);
}

Chapter::~Chapter()
{
    
}
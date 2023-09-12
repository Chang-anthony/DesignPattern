#include "../include/Chapter.hpp"
#include "../include/Mission.hpp"

Chapter::Chapter(/* args */)
{
    this->missions = std::set<Mission*>();
}

void Chapter::AddMission(Mission* mission)
{
    this->missions.insert(mission);
}

Chapter::~Chapter()
{
}
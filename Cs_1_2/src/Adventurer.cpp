#include "../include/Adventurer.h"
#include "../include/TourGroup.h"
#include "../include/Journey.h"
#include "../include/Student.h"
#include "../include/Mission.h"

Adventurer::Adventurer()
{
    id = 0;
    group = nullptr;
}

Adventurer::Adventurer(int id,Student* student,Journey* journey)
{
    GetID();
    SetStudent(student);
    SetJourney(journey);
}

void Adventurer::CarryOnMission(Mission* mission)
{
    this->student->CarryMission(utils::RequireNonNull(mission));
}

int Adventurer::GetID()
{
    return this->id;
}

TourGroup* Adventurer::GetTourGroup()
{
    return this->group;
}

Student* Adventurer::GetStudent()
{
    return this->student;
}

Journey* Adventurer::GetJourney()
{
    return this->journey;
}

void Adventurer::SetID(int id)
{
    utils::ValShouldBigger(id,0);
    this->id = id;
}

void Adventurer::SetTourGroup(TourGroup* group)
{
    utils::RequireNonNull(group);
    this->group = group;
}

void Adventurer::SetJourney(Journey* journey)
{
    utils::RequireNonNull(journey);
    this->journey = journey;
}

void Adventurer::SetStudent(Student* student)
{
    utils::RequireNonNull(student);
    this->student = student;
}

Adventurer::~Adventurer()
{

}
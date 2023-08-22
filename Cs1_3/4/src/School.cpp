#include "../include/School.hpp"
#include "../include/Classroom.hpp"

School::School()
{
    this->classrooms = std::set<Classroom*>();
}

void School::AddClassroom(Classroom* classroom)
{
    this->classrooms.insert(classroom);
}

School::~School()
{

}
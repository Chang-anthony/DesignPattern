#include "../include/Teacher.hpp"
#include "../include/School.hpp"

Teacher::Teacher(/* args */)
{
    this->school = new School();
}

void Teacher::WorkInSchool(School* school)
{
    this->school = school;
}

Teacher::~Teacher()
{
    
}
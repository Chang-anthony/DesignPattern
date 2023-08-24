#include "../include/Student.hpp"
#include "../include/School.hpp"

Student::Student(/* args */)
{
    
}

School* Student::GetSchool()
{
    return this->school;
}

void Student::SetSchool(School* school)
{
    this->school = school;
}

Student::~Student()
{

}
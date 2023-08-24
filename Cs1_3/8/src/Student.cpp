#include "../include/Student.hpp"
#include "../include/Registration.hpp"

Student::Student(/* args */)
{
    
}

Registration* Student::GetRegisration()
{
    return this->registeration;
}

void Student::SetRegisration(Registration* registeration)
{
    this->registeration = registeration;
}

Student::~Student()
{

}
#include "../include/School.hpp"
#include "../include/Registration.hpp"
#include "../include/Student.hpp"


School::School(/* args */)
{
    this->registers = std::set<Registration*>();
}

Registration* School::Register(Student* student,int score)
{
    Registration* regis = new Registration(this,student,score);
    this->registers.insert(regis);
    student->SetRegisration(regis);
    return regis;
}


std::set<Registration*> School::GetRegister()
{
    return this->registers;
}

void School::SetRegister(std::set<Registration*> registers)
{
    this->registers = registers;
}

School::~School()
{
}
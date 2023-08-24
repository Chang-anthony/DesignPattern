#include "../include/School.hpp"
#include "../include/Registration.hpp"
#include "../include/Student.hpp"


School::School(/* args */)
{
    this->students = std::set<Student*>();
    this->registers = std::set<Registration*>();
}

Registration* School::Register(Student* student,int score)
{
    this->students.insert(student);
    Registration* regis = new Registration(this,student,score);
    this->registers.insert(regis);
    student->SetSchool(this);
    return regis;
}

std::set<Student*> School::GetStudents()
{
    return this->students;
}

std::set<Registration*> School::GetRegister()
{
    return this->registers;
}

void School::SetStudents(std::set<Student*> students)
{
    this->students = students;
}
void School::SetRegister(std::set<Registration*> registers)
{
    this->registers = registers;
}

School::~School()
{
}
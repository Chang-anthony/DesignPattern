#include "../include/Studnet.hpp"
#include "../include/Teacher.hpp"

Student::Student(/* args */)
{
    //this->teachers = std::vector<Teacher*>();
    this->teachers = std::set<Teacher*>();
}

void Student::AddTeacher(Teacher* teacher)
{   
    this->teachers.insert(teacher);
}

// std::vector<Teacher*> Student::GetTeachers()
// {
//     return this->teachers;
// }

// void Student::SetTeachers(std::vector<Teacher*> teachers)
// {
//     this->teachers = teachers;
// }

Student::~Student()
{
}
#include "../include/School.hpp"
#include "../include/Teacher.hpp"

School::School()
{
    this->teachers = std::set<Teacher*>();
}

void School::Employ(Teacher* teacher)
{
    std::cout << "this school employ this teacher" << std::endl;
    //建立雙向關聯
    this->teachers.insert(teacher);
    teacher->WorkInSchool(this);
}

School::~School()
{

}
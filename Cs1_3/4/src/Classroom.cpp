#include "../include/Classroom.hpp"
#include "../include/School.hpp"

Classroom::Classroom(School* school):school(school)
{
    std::cout << "this school have this classroom" << std::endl;
    //建立單向關聯，因為是學校包含此教室，沒有學校就沒有教室，
    //所以教室不需要知道它存在於哪個學校內，為複合的概念並且為單向關聯
    this->school->AddClassroom(this);
}

Classroom::~Classroom()
{

}
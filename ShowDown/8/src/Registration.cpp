#include "../include/Registration.hpp"
#include "../include/School.hpp"
#include "../include/Student.hpp"

Registration::Registration(School* school,Student* student,int score)
            :school(school),student(student),score(score)
{

}

Registration::~Registration()
{
}
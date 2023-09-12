#include "../include/Employee.hpp"



Employee::Employee(/* args */):is_teacher(false),is_excutive(false)
{

}

bool Employee::GetIsTeacher()
{
    return this->is_teacher;
}
bool Employee::GetIsExcutive()
{
    return this->is_excutive;
}


void Employee::SetIsTeacher(bool is_teacher)
{
    this->is_teacher = is_teacher;
}

void Employee::SetIsExcutive(bool is_excutive)
{
    this->is_excutive = is_excutive;
}

Employee::~Employee()
{
    
}

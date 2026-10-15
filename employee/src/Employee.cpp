#include "Employee.hpp"
#include "utils.h"

Employee::Employee(int id, std::string name, int age)
{
    this->id = id;
    this->name = name;
    this->age = age;
    subordinates = std::vector<Employee*>();
}

Employee::Employee(int id, std::string name, int age, std::vector<Employee*> subordinates)
{
    this->id = id;
    this->name = name;
    this->age = age;
    this->subordinates = subordinates;
}

int Employee::getId() const
{
    return id;
}

std::string Employee::getName() const
{
    return name;
}

int Employee::getAge() const
{
    return age;
}

std::vector<Employee*> Employee::getSubordinates() const
{
    return subordinates;
}

Employee::~Employee()
{
}
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

Employee::~Employee()
{
}
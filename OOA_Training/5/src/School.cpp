#include "../include/School.hpp"
#include "../include/Employee.hpp"

School::School()
{
    this->employees = std::set<Employee*>();
}

void School::Employ(Employee* employee)
{
    this->employees.insert(employee);
}

School::~School()
{

}
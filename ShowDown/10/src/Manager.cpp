#include "../include/Manager.hpp"

Manager::Manager():Employee()
{
    this->employees = std::set<Employee*>();
}

void Manager::Manage(Employee* employee)
{
    employee->SetManager(this);
    this->employees.insert(employee);
}

Manager::~Manager()
{
}
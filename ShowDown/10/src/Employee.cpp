#include "../include/Manager.hpp"
#include "../include/Employee.hpp"

Employee::Employee()
{
    this->manager = nullptr;
}

void Employee::SetManager(Manager* manager)
{
    this->manager = manager;
}

Employee::~Employee()
{

}

#include <RealEmployee.hpp>

RealEmployee::RealEmployee(int id, std::string name, int age)
    :Employee(id, name, age)
{
}

RealEmployee::RealEmployee(int id, std::string name, int age, std::vector<Employee*> subordinates)
    :Employee(id, name, age, subordinates)
{
}

RealEmployee::~RealEmployee()
{
}

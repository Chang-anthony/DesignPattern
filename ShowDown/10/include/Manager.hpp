#ifndef _MANAGER_H_
#define _MANAGER_H_


#include <iostream>
#include <set>
#include <vector>
#include "../include/Employee.hpp"


class Manager:Employee
{
private:
    /* data */
    std::set<Employee*> employees;
public:
    Manager();
    ~Manager();

    
    void Manage(Employee* employee);
};





#endif /* _MANAGER_H_ */

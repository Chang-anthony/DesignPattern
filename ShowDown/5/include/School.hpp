#ifndef _SCHOOL_H_
#define _SCHOOL_H_

#include <iostream>
#include <set>
#include <vector>
#include "../include/utils/utils.h"

class Employee;

class School
{
private:
    /* data */
    std::set<Employee*> employees;
public:
    School(/* args */);
    ~School();

    void Employ(Employee* employee);
};

#endif // __SCHOOL_H__
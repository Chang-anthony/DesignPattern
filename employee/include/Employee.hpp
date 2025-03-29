#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_


#include <string>
#include <iostream>
#include <vector>

class Employee
{
private:
    /* data */
    int id;
    std::string name;
    int age;
    std::vector<Employee*> subordinates;
public:
    Employee(int id, std::string name, int age);
    Employee(int id, std::string name, int age, std::vector<Employee*> subordinates);
    ~Employee();
};


#endif /* _EMPLOYEE_H_ */

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

    int getId() const;
    std::string getName() const;
    int getAge() const;
    std::vector<Employee*> getSubordinates() const;
};


#endif /* _EMPLOYEE_H_ */

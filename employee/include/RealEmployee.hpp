#ifndef _REALEMPLOYEE_H_
#define _REALEMPLOYEE_H_


#include <string>
#include <iostream>
#include <Employee.hpp>

class RealEmployee : public Employee
{
private:
    /* data */
public:
    RealEmployee(int id, std::string name, int age);
    RealEmployee(int id, std::string name, int age, std::vector<Employee*> subordinates);
    ~RealEmployee();

};

#endif /* _REALEMPLOYEE_H_ */

#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_


class Manager;

class Employee
{
private:
    /* data */
    Manager* manager;
public:
    Employee();
    ~Employee();

    void SetManager(Manager* manager);
};

#endif /* _EMPLOYEE_H_ */

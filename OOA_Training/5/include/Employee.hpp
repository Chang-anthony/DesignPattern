#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

#include <iostream>

class Employee
{
private:
    /* data */
    bool is_teacher;
    bool is_excutive;
public:
    Employee();
    ~Employee();

    //getter
    bool GetIsTeacher();
    bool GetIsExcutive();

    //setter
    void SetIsTeacher(bool is_teacher);
    void SetIsExcutive(bool is_excutive);

};




#endif // __EMPLOYEE_H__
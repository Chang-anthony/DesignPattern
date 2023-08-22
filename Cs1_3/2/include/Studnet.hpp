#ifndef _STUDNET_H_
#define _STUDNET_H_

#include <iostream>
#include <string>
#include <vector>
#include "../include/utils/utils.h"

class Teacher;

class Student
{
private:
    /* data */
    std::vector<Teacher*> teachers;
public:
    Student(/* args */);
    ~Student();

    //getter
    std::vector<Teacher*> GetTeachers();

    //setter
    void SetTeachers(std::vector<Teacher*> teachers);
    
};


#endif // __STUDNET_H__
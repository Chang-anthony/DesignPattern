#ifndef _STUDNET_H_
#define _STUDNET_H_

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "../include/utils/utils.h"

class Teacher;

class Student
{
    
private:
    /* data */
    std::set<Teacher*> teachers;
    //std::vector<Teacher*> teachers;
public:
    Student(/* args */);
    ~Student();

    void AddTeacher(Teacher* teacher);
    //getter
    //std::vector<Teacher*> GetTeachers();

    //setter
    //void SetTeachers(std::vector<Teacher*> teachers);
    
};


#endif // __STUDNET_H__
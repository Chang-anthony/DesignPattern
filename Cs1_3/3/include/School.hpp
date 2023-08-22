#ifndef _SCHOOL_H_
#define _SCHOOL_H_

#include <iostream>
#include <set>
#include <vector>
#include "../include/utils/utils.h"

class Teacher;

class School
{
private:
    /* data */
    std::set<Teacher*> teachers;
public:
    School(/* args */);
    ~School();

    void Employ(Teacher* teacher);
};

#endif // __SCHOOL_H__
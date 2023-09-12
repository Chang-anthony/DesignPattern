#ifndef _TEACHER_H_
#define _TEACHER_H_

#include <iostream>
#include <set>
#include <vector>
#include "../include/utils/utils.h"

class School;

class Teacher
{
private:
    /* data */
    School* school;
public:
    Teacher(/* args */);
    ~Teacher();

    void WorkInSchool(School* school);
};

#endif // __TEACHER_H__
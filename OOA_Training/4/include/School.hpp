#ifndef _SCHOOL_H_
#define _SCHOOL_H_

#include <iostream>
#include <set>
#include <vector>
#include "../include/utils/utils.h"

class Classroom;

class School
{
private:
    /* data */
    std::set<Classroom*> classrooms;
public:
    School(/* args */);
    ~School();

    void AddClassroom(Classroom* classroom);
};

#endif // __SCHOOL_H__
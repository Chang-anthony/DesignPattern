#ifndef _TEACHER_H_
#define _TEACHER_H_

#include "../include/utils/utils.h"

class Handout;
class Teacher
{
private:
    /* data */
public:
    Teacher(/* args */);
    ~Teacher();

    void Teach(Handout* handout);
};





#endif // __TEACHER_H__
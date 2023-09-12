#ifndef _REGISTRATION_H_
#define _REGISTRATION_H_

class Student;
class School;

class Registration
{
private:
    /* data */
    Student* student;
    School* school;
    int score;
public:
    Registration(School* school,Student* student,int score);
    ~Registration();
};


#endif // _REGISTRATION_H_
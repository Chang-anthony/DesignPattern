#ifndef _STUDENT_H_
#define _STUDENT_H_

class School;
class Student
{
private:
    /* data */
    School* school;
public:
    Student(/* args */);
    ~Student();

    //getter
    School* GetSchool();

    //setter
    void SetSchool(School* school);
};




#endif /* _STUDENT_H_ */

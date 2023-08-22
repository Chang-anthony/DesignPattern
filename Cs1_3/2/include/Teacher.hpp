#ifndef _TEACHER_H_
#define _TEACHER_H_

#include "../include/utils/utils.h"

class Student;

class Teacher
{
private:
    /* data */
    std::vector<Student*> students;
public:
    Teacher(/* args */);
    ~Teacher();

    void Teach(Student* student);

    //getter
    std::vector<Student*> GetStudents();

    //setter
    void SetStudents(std::vector<Student*> students);

};



#endif // __TEACHER_H__
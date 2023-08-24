#ifndef _SCHOOL_H_
#define _SCHOOL_H_

#include <iostream>
#include <set>
#include <vector>

class Student;
class Registration;
class School
{
private:
    /* data */
    std::set<Student*> students;
    std::set<Registration*> registers;
public:
    School();
    ~School();

    Registration* Register(Student* student,int score);

    //getter
    std::set<Student*> GetStudents();
    std::set<Registration*> GetRegister();

    //setter
    void SetStudents(std::set<Student*> students);
    void SetRegister(std::set<Registration*> registers);
};




#endif /* _SCHOOL_H_ */

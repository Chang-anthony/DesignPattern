#ifndef _STUDENT_H_
#define _STUDENT_H_

class Registration;
class Student
{
private:
    /* data */
    Registration* registeration;
public:
    Student(/* args */);
    ~Student();

    //getter
    Registration* GetRegisration();

    //setter
    void SetRegisration(Registration* registeration);
};




#endif /* _STUDENT_H_ */

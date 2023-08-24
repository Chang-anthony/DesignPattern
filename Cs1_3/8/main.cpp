/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "../include/School.hpp"
#include "../include/Registration.hpp"
#include "../include/Student.hpp"

int main()
{
    School* nkust = new School();
    Student* me = new Student();
    Student* one = new Student();
    Student* two = new Student();

    nkust->Register(me,90);
    nkust->Register(one,60);
    nkust->Register(two,100);
    

    // std::cout << "test" << std::endl;
    return 0;
}
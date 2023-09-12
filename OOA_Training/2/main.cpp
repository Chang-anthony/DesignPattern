/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "../include/Teacher.hpp"
#include "../include/Studnet.hpp"

int main()
{
    Teacher* teacher = new Teacher();
    Student* anthony = new Student();
    teacher->Teach(anthony);
    // std::cout << "test" << std::endl;
    return 0;
}
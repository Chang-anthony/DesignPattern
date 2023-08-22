/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "../include/Classroom.hpp"
#include "../include/School.hpp"

int main()
{
    School* nkust = new School();
    Classroom* classroom1 = new Classroom();
    Classroom* classroom2 = new Classroom();
    nkust->AddClassroom(classroom1);
    nkust->AddClassroom(classroom2);

    // std::cout << "test" << std::endl;
    return 0;
}
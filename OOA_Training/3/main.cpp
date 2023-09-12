/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "../include/Teacher.hpp"
#include "../include/School.hpp"

int main()
{
    School* nkust = new School();
    Teacher* teacher = new Teacher();
    nkust->Employ(teacher);
    // std::cout << "test" << std::endl;
    return 0;
}
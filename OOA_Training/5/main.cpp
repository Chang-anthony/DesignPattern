/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "../include/Teacher.hpp"
#include "../include/Executive.hpp"
#include "../include/Employee.hpp"
#include "../include/School.hpp"

int main()
{
    School* nkust = new School();
    Teacher* teacher = new Teacher();
    Executive* executive = new Executive();
    nkust->Employ(teacher);
    nkust->Employ(executive);
    
    // std::cout << "test" << std::endl;
    return 0;
}
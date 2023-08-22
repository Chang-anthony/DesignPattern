/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "../include/Teacher.hpp"
#include "../include/Handout.hpp"

int main()
{
    Teacher* teacher = new Teacher();
    Handout* math = new Handout();
    teacher->Teach(math);
    // std::cout << "test" << std::endl;
    return 0;
}
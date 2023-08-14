/*
* @author - a23011257@gmail.com (Anthony)
*/
#include <iostream>
#include <stdio.h>
#include "include/Student.h"


int main()
{
    std::cout <<"hello world!!!" << std::endl;
    // int* object = 0;
    // requireNonNull(object);
    Student test = Student("Anthony","123545");
    test.GainExp(3000);
    return 0;
}
/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "../include/Classmate.hpp"

int main()
{
    Classmate* me = new Classmate();
    Classmate* one = new Classmate();
    Classmate* two = new Classmate();

    me->makefriend(one);
    me->makefriend(two);

    // std::cout << "test" << std::endl;
    return 0;
}
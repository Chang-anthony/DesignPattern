/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "../include/Preson.hpp"
#include "../include/Marry.hpp"
#include "../include/Love.hpp"


int main()
{
    Preson* p1 = new Preson();
    Preson* p2 = new Preson();

    Love* inlove = p1->InLove(p2);
    Marry* marry1 =  inlove->Domarry();

    marry1->Divorce(10);

    marry1->Divorce(9);

    
    // std::cout << "test" << std::endl;
    return 0;
}
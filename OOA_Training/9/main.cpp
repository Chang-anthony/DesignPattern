/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "../include/Road.hpp"
#include "../include/City.hpp"

int main()
{
    City* A = new City();
    City* B = new City();

    Road* A_B = A->Connect(B);

    return 0;
}
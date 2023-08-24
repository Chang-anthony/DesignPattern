/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "../include/Hero.hpp"



int main()
{
    Hero* A = new Hero();
    Hero* B = new Hero();
    Hero* C = new Hero();
    Hero* D = new Hero();

    std::vector<Hero*> heros{A,B,C,D};

    A->SetHeros(heros);
    A->TakeTurn();

    return 0;
}
/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "../include/World.hpp"
#include "../include/Adventurer.hpp"


int main()
{
    World* world = new World();
    Adventurer* adventurer = new Adventurer(world);

    for(int i = 0 ; i < 50 ;i++)
        adventurer->RolltheDice();

    return 0;
}
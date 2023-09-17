/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "../include/MatchSystem.hpp"
#include "../include/MatchType.hpp"
#include "../include/Individual.hpp"
#include "../include/Coord.hpp"
#include "../include/Habit.hpp"
#include "../include/DistanceBase.hpp"
#include "../include/Habit.hpp"


int main()
{
    MatchSystem* system = new MatchSystem(new DistanceBase());

    Individual* one = new Individual(18,"MALE",new Coord(1,0),
                        "Hi my name is one",false,{new Habit("1"),new Habit("2"),new Habit("3")});
    
    Individual* two = new Individual(18,"MALE",new Coord(1,-1),
                "Hi my name is two",false,{new Habit("1"),new Habit("2"),new Habit("3")});

    Individual* two = new Individual(18,"MALE",new Coord(1,-1),
                "Hi my name is two",false,{new Habit("1"),new Habit("2"),new Habit("3")});

    std::system("pause");
    return 0;
}
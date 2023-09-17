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
#include "../include/HabitBase.hpp"


int main()
{
    MatchSystem* system = new MatchSystem(new HabitBase());

    Individual* one = new Individual(18,"MALE",new Coord(1,0),
                        "Hi my name is one",false,{new Habit("1"),new Habit("2"),new Habit("3")});
    
    Individual* two = new Individual(19,"MALE",new Coord(2,-1),
                "Hi my name is two",false,{new Habit("2"),new Habit("3"),new Habit("5")});

    Individual* three = new Individual(21,"FEMALE",new Coord(1,-1),
                "Hi my name is two",false,{new Habit("1"),new Habit("2"),new Habit("3")});

    system->AddIndividuals(one);
    system->AddIndividuals(two);
    system->AddIndividuals(three);

    Individual* matched = system->Match(one);
    std::cout << "Age :" << matched->GetAge() << std::endl;

    std::system("pause");
    return 0;
}
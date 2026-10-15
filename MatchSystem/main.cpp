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
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif


int main()
{
#ifdef _WIN32
    // 原始碼是 UTF-8，將 console 輸出改為 UTF-8 才能正確顯示中文
    SetConsoleOutputCP(CP_UTF8);
#endif
    MatchSystem* system = new MatchSystem(new HabitBase());

    Individual* one = new Individual(18,"MALE",new Coord(1,0),
                        "Hi my name is one",{new Habit("1"),new Habit("2"),new Habit("3")});
    
    Individual* two = new Individual(19,"MALE",new Coord(2,-1),
                "Hi my name is two",{new Habit("2"),new Habit("3"),new Habit("5")});

    Individual* three = new Individual(21,"FEMALE",new Coord(1,-1),
                "Hi my name is two",{new Habit("1"),new Habit("2"),new Habit("3")});

    system->AddIndividuals(one);
    system->AddIndividuals(two);
    system->AddIndividuals(three);

    Individual* matched = system->Match(one);
    std::cout << "Age :" << matched->GetAge() << std::endl;

    std::system("pause");
    return 0;
}
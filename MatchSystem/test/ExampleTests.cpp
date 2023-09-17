#include <gtest/gtest.h>
#include "../include/MatchSystem.hpp"
#include "../include/MatchType.hpp"
#include "../include/Individual.hpp"
#include "../include/Coord.hpp"
#include "../include/Habit.hpp"
#include "../include/DistanceBase.hpp"
#include "../include/HabitBase.hpp"

TEST(DISTANCEBASE,DISTANCEBASE_TEST)
{
    MatchSystem* system = new MatchSystem(new DistanceBase());

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
    EXPECT_EQ(21,matched->GetAge());
}

TEST(DISTANCEBASE_REVERSE,DISTANCEBASE_REVERSE_TEST)
{
    MatchSystem* system = new MatchSystem(new DistanceBase());

    Individual* one = new Individual(18,"MALE",new Coord(1,0),
                        "Hi my name is one",true,{new Habit("1"),new Habit("2"),new Habit("3")});
    
    Individual* two = new Individual(19,"MALE",new Coord(2,-1),
                "Hi my name is two",false,{new Habit("2"),new Habit("3"),new Habit("5")});

    Individual* three = new Individual(21,"FEMALE",new Coord(1,-1),
                "Hi my name is two",false,{new Habit("1"),new Habit("2"),new Habit("3")});

    system->AddIndividuals(one);
    system->AddIndividuals(two);
    system->AddIndividuals(three);

    Individual* matched = system->Match(one);
    EXPECT_EQ(19,matched->GetAge());
}


TEST(HABITBASE,HABITBASE_TEST)
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
    EXPECT_EQ(21,matched->GetAge());
}

TEST(HABITBASE_REVERSE,HABITBASE_REVERSE_TEST)
{
    MatchSystem* system = new MatchSystem(new HabitBase());

    Individual* one = new Individual(18,"MALE",new Coord(1,0),
                        "Hi my name is one",true,{new Habit("1"),new Habit("2"),new Habit("3")});
    
    Individual* two = new Individual(19,"MALE",new Coord(2,-1),
                "Hi my name is two",false,{new Habit("2"),new Habit("3"),new Habit("5")});

    Individual* three = new Individual(21,"FEMALE",new Coord(1,-1),
                "Hi my name is two",false,{new Habit("1"),new Habit("2"),new Habit("3")});

    system->AddIndividuals(one);
    system->AddIndividuals(two);
    system->AddIndividuals(three);

    Individual* matched = system->Match(one);
    EXPECT_EQ(19,matched->GetAge());
}
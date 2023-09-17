#include "../include/Individual.hpp"
#include "../include/Coord.hpp"
#include "../include/Habit.hpp"
#include "../include/MatchSystem.hpp"

Individual::Individual(int age,std::string gender,Coord* coord,std::string intro,
                bool reverse,std::vector<Habit*> habits)
{
    SetAge(age);
    SetGender(gender);
    SetIntro(intro);
    SetReverse(reverse);
    SetHabits(habits);
    SetCoord(coord);
}

void Individual::AddHabit(Habit* habit)
{
    utils::RequireNonNull(habit);
    this->habits.push_back(habit);
}

void Individual::SetID(int id)
{
    this->id = id;
}

void Individual::SetAge(int age)
{
    utils::ValShouldBigger(age,17);
    this->age = age;
}

void Individual::SetGender(std::string gender)
{
    if(gender != "MALE" || gender != "FEMALE")
    {
        std::invalid_argument("gender only can set MALE or FEMALE");
    }
    this->gender = gender;
}

void Individual::SetIntro(std::string intro)
{
    utils::LengthShouldBe(intro,0,200);
    this->intro = intro;
}

void Individual::SetCoord(Coord* coord)
{
    utils::RequireNonNull(coord);
    this->coord = coord;
}

void Individual::SetReverse(bool reverse)
{
    this->reverse = reverse;
}

void Individual::SetHabits(std::vector<Habit*> habits)
{
    utils::RequireNonNull(&habits);
    this->habits = habits;
}

int Individual::GetID()
{
    return id;
}

int Individual::GetAge()
{
    return age;
}

std::string Individual::GetIntro()
{
    return intro;
}

std::string Individual::GetGender()
{
    return gender;
}


bool Individual::GetReverse()
{
    return reverse;
}

Coord* Individual::GetCoord()
{
    return coord;
}

std::vector<Habit*> Individual::GetHabits()
{
    return habits;
}

Individual::~Individual()
{
}

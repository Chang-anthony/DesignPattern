#include "../include/Individual.hpp"
#include "../include/Coord.hpp"
#include "../include/Habit.hpp"
#include "../include/MatchSystem.hpp"

Individual::Individual(int age,std::string gender,Coord* coord,std::string intro,
                std::string prefermatch,bool reverse,std::vector<Habit*> habits,MatchSystem* system)
{
    SetMatchSystem(system);
    SetID();
    SetAge(age);
    SetGender(gender);
    SetIntro(intro);
    SetPreferMatch(prefermatch);
    SetReverse(reverse);
    SetHabits(habits);
    SetCoord(coord);
}

void Individual::AddHabit(Habit* habit)
{
    utils::RequireNonNull(habit);
    this->habits.push_back(habit);
}

void Individual::SetID()
{
    this->id = GetMatchSystem()->GetIndividuals().size() + 1;
}

void Individual::SetMatchSystem(MatchSystem* system)
{
    utils::RequireNonNull(system);
    this->system = system;
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

void Individual::SetPreferMatch(std::string prefermatch)
{
    this->prefermatch = prefermatch;
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

std::string Individual::GetPreferMatch()
{
    return prefermatch;
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

MatchSystem* Individual::GetMatchSystem()
{
    return system;
}

Individual::~Individual()
{
}

#include "../include/Habit.hpp"


Habit::Habit(std::string habit)
{
    SetHabit(habit);
}

std::string Habit::GetHabit()
{
    return this->habit;
}

void Habit::SetHabit(std::string habit)
{
    utils::LengthShouldBe(habit,1,10);
    this->habit = habit;
}

Habit::~Habit()
{
}
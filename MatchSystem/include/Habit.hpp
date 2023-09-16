#ifndef _HABIT_H_
#define _HABIT_H_

#include <iostream>
#include <vector>
#include <string>
#include "../include/utils/utils.h"

class Habit
{
private:
    /* data */
    std::string habit;
public:
    Habit(std::string habit);
    ~Habit();

    //getter
    std::string GetHabit();


    //setter
    void SetHabit(std::string habit);
};

#endif /* _HABIT_H_ */

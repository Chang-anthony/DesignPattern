#ifndef _INDIVIDUAL_H_
#define _INDIVIDUAL_H_

#include <iostream>
#include <string>
#include <vector>
#include "../include/utils/utils.h"

class Habit;
class Coord;


class Individual
{
private:
    /* data */
    int id;
    int age;
    std::string gender;
    Coord* coord;
    std::vector<Habit*> habits;
    std::string intro;
    std::string prefermatch;
    bool reverse;
public:
    Individual(int id,int age,std::string gender,Coord* coord,std::string intro,
                std::string prefermatch,bool reverse,std::vector<Habit*> habits);
    ~Individual();

    void AddHabit(Habit* habit);

    //getter
    int GetID();
    int GetAge();
    std::string GetGender();
    Coord* GetCoord();
    std::string GetIntro();
    std::string GetPreferMatch();
    bool GetReverse();
    std::vector<Habit*> GetHabits();

    //setter
    void SetID(int id);
    void SetAge(int age);
    void SetGender(std::string gender);
    void SetCoord(Coord* coord);
    void SetIntro(std::string intro);
    void SetPreferMatch(std::string prefermatch);
    void SetReverse(bool reverse);
    void SetHabits(std::vector<Habit*> habits);
};

#endif /* _INDIVIDUAL_H_ */

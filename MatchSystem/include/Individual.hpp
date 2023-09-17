#ifndef _INDIVIDUAL_H_
#define _INDIVIDUAL_H_

#include <iostream>
#include <string>
#include <vector>
#include "../include/utils/utils.h"

class MatchSystem;
class Habit;
class Coord;


class Individual
{
private:
    /* data */
    MatchSystem* system;

    int id;
    int age;
    std::string gender;
    Coord* coord;
    std::vector<Habit*> habits;
    std::string intro;
    std::string prefermatch;
    bool reverse;
public:
    Individual(int age,std::string gender,Coord* coord,std::string intro,
                std::string prefermatch,bool reverse,std::vector<Habit*> habits,MatchSystem* system);
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
    MatchSystem* GetMatchSystem();

    //setter
    void SetID();
    void SetAge(int age);
    void SetGender(std::string gender);
    void SetCoord(Coord* coord);
    void SetIntro(std::string intro);
    void SetPreferMatch(std::string prefermatch);
    void SetReverse(bool reverse);
    void SetHabits(std::vector<Habit*> habits);
    void SetMatchSystem(MatchSystem* system);
};

#endif /* _INDIVIDUAL_H_ */

#pragma once
#ifndef _JOURNEY_H_
#define _JOURNEY_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdlib>
#include "../include/utils/utils.h"
// #include "Chapter.h"


class Chapter;
class Adventurer;
class Student;
class TourGroup;
class Mission;

//因為Journey 底下有很多 Chapter 所以為單向複合關聯，Journey必須要知道自己底下有多少Chapter
//Since there are multiple Chapters under Journey, it forms a unidirectional composition association.
//Journey needs to be aware of how many Chapters it contains.

class Journey
{
private:
    std::string name;
    std::string description;
    int price;
    std::vector<Chapter*> chapters;
    std::vector<Adventurer*> adventurers;
    std::vector<TourGroup*> tourgroups;
public:
    Journey(std::string name,std::string description,
            int price,const std::vector<Chapter*>& chapters,
            const std::vector<Adventurer*>& adventurers
            ,const std::vector<TourGroup*>& tourgroups);
    ~Journey();

    Adventurer* Join(Student* studnet);
    Mission* FirstMission();
    TourGroup* MatchTourGroup(Adventurer* adventurer);

    //getter
    std::string GetName();
    std::string GetDescription();
    int GetPrice();
    std::vector<Chapter*> GetChapters();
    std::vector<Adventurer*> GetAdventurers();
    std::vector<TourGroup*> GetTourGroups();

    //setter
    void SetName(std::string name);
    void SetDescription(std::string description);
    void SetPrice(int price);
    void SetChapters(const std::vector<Chapter*>& chapter);
    void SetAdventurers(const std::vector<Adventurer*>& adventurers);
    void SetTourGroups(const std::vector<TourGroup*>& tourgroups);
};



#endif
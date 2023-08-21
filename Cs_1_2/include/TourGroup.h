#ifndef _TOURGROUP_H_
#define _TOURGROUP_H_
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "../include/utils/utils.h"

class Adventurer;

class TourGroup
{
private:
    int id;
    std::vector<Adventurer*> adventurers;
public:
    TourGroup(/* args */);
    TourGroup(int id,const std::vector<Adventurer*>& adventurer);
    ~TourGroup();

    void Add(Adventurer* adventurer);

    //getter
    int GetID();
    std::vector<Adventurer*> GetAdventurers();

    //setter
    void SetID(int id);
    void SetAdventurers(const std::vector<Adventurer*>& adventurers);
};
#endif // __TOURGROUP_H__
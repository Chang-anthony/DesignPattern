#ifndef _ADVENTURER_H_
#define _ADVENTURER_H_
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "../include/utils/utils.h"

class TourGroup;
class Student;//是哪個 student 變成 冒險者的
class Journey;//此冒險者參加甚麼主題旅程
class Mission;//要讓此冒險者做甚麼主線任務

class Adventurer
{
private:
    int id;
    TourGroup* group;
    Journey* journey;
    Student* student;
public:
    Adventurer();
    Adventurer(int id,Student* student,Journey* journey);
    ~Adventurer();

    //分配任務
    void CarryOnMission(Mission* mission);

    //getter
    int GetID();
    TourGroup* GetTourGroup();
    Journey* GetJourney();
    Student* GetStudent();

    //setter
    void SetID(int id);
    void SetTourGroup(TourGroup* group);
    void SetJourney(Journey* journey);
    void SetStudent(Student* student);
};


#endif // __ADVENTURER_H__
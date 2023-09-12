#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

class Student;
class Mission;

//Forward declaration 
//use this technical need to create file CheckMissionstate.cpp and need to implemnt function in this file

/*
 關聯類別 Associated class
 因為我要知道是哪個學生在做這個任務，並且該學生會可以查詢他自己的完成狀態 
Because I want to know which student is doing this task, and the student union can query his own completion status
 所以初始化給予 哪個學生需要做個任務
So the initialization gives which student needs to do a task
*/

class CheckMissionState
{

private:
    enum state 
    {inprogress,done};
    state currentstate;
    Student *student;
    Mission *mission;
public:
    CheckMissionState(Student *student,Mission *mission);
    ~CheckMissionState();
    void CompleteMission();

    //getter
    Student* GetStuent();
    Mission* GetMission();

    //setter
    void SetStudent(Student* student);
    void SetMission(Mission *mission);
};


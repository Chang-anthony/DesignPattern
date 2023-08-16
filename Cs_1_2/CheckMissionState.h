#ifndef CHECKMISSIONSTATE_H
#define CHECKMISSIONSTATE_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "include/utils.h"
#include "Student.h"
#include "Mission.h"

/*
關聯類別 Associated class
因為我要知道是哪個學生在做這個任務，並且該學生會可以查詢他自己的完成狀態 
Because I want to know which student is doing this task, and the student union can query his own completion status
所以初始化給予 哪個學生需要做個任務
So the initialization gives which student needs to do a task
*/

//TODO : need to fix
class CheckMissionState
{

private:
    enum state 
    {inprogress,done};
    state currentstate;
    // Student* studnet;
    // Mission* mission;
public:
    CheckMissionState()
    {
        this->currentstate = state::inprogress;
        // this->student = student;
        // this->mission = mission;
    };
    ~CheckMissionState(){};
    void CompleteMission();
};

void CheckMissionState::CompleteMission()
{
    this->currentstate = state::done;
    // std::cout << "任務】學員 " << studnet->GetAccount() << " 已成功完成任務" << mission->GetName() << std::endl;
    // student->GainExp(CheckMissionState::mission->ExpAward());
}


#endif // CHECKMISSIONSTATE_H
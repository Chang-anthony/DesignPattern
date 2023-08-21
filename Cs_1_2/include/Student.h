// #pragma once
#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
// #include "CheckMissionState.h"
// #include "Mission.h"
// #include "LevelSheet.h"

//Forward declaration
class Mission;
class LevelSheet;//Because Studnet Dependency on LevelSheet
class CheckMissionState;

class Student
{
private:
    LevelSheet* levelsheet;
    std::string account;
    std::string password;
    int level = 1;
    int exp = 0;

    //學生可以透過這個了解自己有多少任務要做
    //Students can use this to understand how much mission they have to do
    std::vector<CheckMissionState*> missioncarryon;
public:
    Student();
    Student(std::string account,std::string password,std::vector<CheckMissionState*> missioncarryon);
    // {
    //     SetAccount(account);
    //     SetPassword(password);
    //     SetCheckMissionState(missioncarryon);
    // };
    ~Student();

    void GainExp(int exp);
    void LevelUp();
    //讓學生有這個任務要做 Give students this mission to do    
    CheckMissionState* CarryMission(Mission* mission);
    
    //getter
    std::string GetAccount();
    std::vector<CheckMissionState*> GetMissionState();

    //setter
    void SetAccount(std::string account);
    void SetPassword(std::string password);
    void SetCheckMissionState(std::vector<CheckMissionState*> missioncarryon);

protected: 

};


#endif




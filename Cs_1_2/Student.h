#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "LevelSheet.h" //Because Studnet Dependency on LevelSheet
#include "CheckMissionState.h"
#include "Mission.h"


class Student
{
private:
    LevelSheet* levelsheet = new LevelSheet();
    std::string account;
    std::string password;
    int level = 1;
    int exp = 0;

    //學生可以透過這個了解自己有多少任務要做
    //Students can use this to understand how much mission they have to do
    std::vector<CheckMissionState*> missioncarryon;


public:
    Student(std::string account,std::string password,std::vector<CheckMissionState*> missioncarryon)
    {
        SetAccount(account);
        SetPassword(password);
        SetCheckMissionState(missioncarryon);
    };
    ~Student(){};

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


void Student::GainExp(int exp)
{
    this->exp += exp;
    int level = levelsheet->queryform(exp);
    // int level = LevelSheet::form(this->exp);
    int uplevel = level - this->level;
    std::cout << "學員 " << this->account << " 獲得經驗值 " << exp << std::endl;
    for(int i = 0 ; i < uplevel; i++)
        this->LevelUp();
}

void Student::LevelUp()
{
    this->level += 1;
    std::cout << "學員 " << this->account << "升級到 " << this->level << std::endl;
}


/*
(單向關聯類別(one-way association class) 
因為只有學生可以查詢他有多少任務需要完成並確認狀態，所以任務那邊不需要知道是哪個學生需要完成他，即單向關聯類別
Because only the student can query how many mission he needs to complete and confirm the status, 
the mission side does not need to know which student needs to complete him, that is, the one-way association category
*/
CheckMissionState* Student::CarryMission(Mission* mission)
{
    std::cout << "【任務】學員 " << this->account << " 開始新任務：" << mission->GetName() << std::endl;
    CheckMissionState* missioncarryon = new CheckMissionState();
    //CheckMissionState* missioncarryon= new CheckMissionState(this,mission);
    this->missioncarryon.push_back(missioncarryon);
    return missioncarryon;
}
    

std::string Student::GetAccount()
{
    return this->account;
}

std::vector<CheckMissionState*> Student::GetMissionState()
{
    return missioncarryon;
}


void Student::SetAccount(std::string account)
{
    this->account = account;
}

void Student::SetPassword(std::string password)
{
    this->password = password;
}

void Student::SetCheckMissionState(std::vector<CheckMissionState*> missioncarryons)
{
    this->missioncarryon = missioncarryons;
}


#endif

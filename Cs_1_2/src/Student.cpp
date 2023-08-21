#include "../include/Student.h"
#include "../include/Mission.h"
#include "../include/LevelSheet.h"
#include "../include/CheckMissionState.h"


Student::Student()
{
    this->levelsheet = new LevelSheet();
    this->account = "";
    this->password = "";
}

Student::Student(std::string account,std::string password,std::vector<CheckMissionState*> missioncarryon)
{
    this->levelsheet = new LevelSheet();
    SetAccount(account);
    SetPassword(password);
    SetCheckMissionState(missioncarryon);
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
    //CheckMissionState* missioncarryon = new CheckMissionState();
    CheckMissionState* missionstate= new CheckMissionState(this,mission);
    this->missioncarryon.push_back(missionstate);
    return missionstate;
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

Student::~Student()
{
    
}

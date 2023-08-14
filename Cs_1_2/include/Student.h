#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "utils/utils.h"
#include "LevelSheet.h" //Because Studnet Dependency on LevelSheet


class Student
{
private:
    LevelSheet* levelsheet = new LevelSheet();
    std::string account;
    std::string password;
    int level = 1;
    int exp = 0;
public:
    Student(std::string account,std::string password):account(account),password(password){};
    ~Student(){};

    void GainExp(int exp);
    void LevelUp();
    //void CheckMissionState(Mission* mission);//TODO:CheckMissionState
    
    //getter
    std::string GetAccount();

    //setter
    void SetAccount(std::string account);
    void SetPassword(std::string password);

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

//TODO:Mission class and Mission
// void Student::CheckMissionState(Mission* mission)
// {

// }
    


std::string Student::GetAccount()
{
    return this->account;
}


void Student::SetAccount(std::string account)
{
    this->account = account;
}

void Student::SetPassword(std::string password)
{
    this->password = password;
}





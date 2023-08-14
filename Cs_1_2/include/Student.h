#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "utils/utils.h"
#include "LevelSheet.h" //Because Studnet Dependency on LevelSheet



class Student
{
private:
    std::string account;
    std::string password;
    int level = 1;
    int exp = 0;
public:
    Student(std::string account,std::string password):account(account),password(password){};
    ~Student(){delete this;};

    void GainExp(int exp);
    void LevelUp();
    
    //getter
    std::string GetAccount();

    //setter
    void SetAccount(std::string account);
    void SetPassword(std::string password);

protected: 

};


void Student::GainExp(int exp)
{
    // TODO : Level Sheet
    return;
}

void Student::LevelUp()
{
    this->level += 1;
}

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





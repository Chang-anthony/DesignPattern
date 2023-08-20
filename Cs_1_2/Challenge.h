#ifndef _CHALLENGE_H_
#define _CHALLENGE_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "include/utils.h"


class Challenge
{
private:
    int id;
    std::string name;
public:
    Challenge(int id,std::string name)
    {
        SetID(id);
        SetName(name);
    };
    ~Challenge(){};

    //getter
    int GetID();
    std::string GetName();

    //setter
    void SetID(int id);
    void SetName(std::string name);
};


int Challenge::GetID()
{
    return this->id;
}

std::string Challenge::GetName()
{
    return this->name;
}

void Challenge::SetID(int id)
{
    utils::ValShouldBigger(id,0);
    this->id = id;
}

void Challenge::SetName(std::string name)
{
    utils::LengthShouldBe(name,1,30);
    this->name = name;
}


#endif 
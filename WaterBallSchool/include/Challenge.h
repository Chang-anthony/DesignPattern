#pragma once
#ifndef _CHALLENGE_H_
#define _CHALLENGE_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "../include/utils/utils.h"


class Challenge
{
private:
    int id;
    std::string name;
public:
    Challenge(int id,std::string name);
    // {
    //     SetID(id);
    //     SetName(name);
    // };
    ~Challenge();

    //getter
    int GetID();
    std::string GetName();

    //setter
    void SetID(int id);
    void SetName(std::string name);
};

#endif 
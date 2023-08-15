#ifndef CHAPTER_H
#define CHAPTER_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "include/utils.h"

class Chapter
{
private:
    int id;
    std::string name;
public:
    Chapter(int id,std::string name)
    {
        SetID(id);
        SetName(name);
    };
    ~Chapter(){};


    //getter
    int GetID();
    std::string GetName();

    //setter
    void SetID(int id);
    void SetName(std::string name);

};

int Chapter::GetID()
{
    return this->id;
}

std::string Chapter::GetName()
{
    return this->name;
}


void Chapter::SetID(int id)
{
    valshouldBigger(id,1);
    this->id = id;
}

void Chapter::SetName(std::string name)
{
    lengthshouldBe(name,1,30);
    this->name = name;
}

#endif
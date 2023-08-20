#ifndef JOURNEY_H
#define JOURNEY_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "Chapter.h"


//因為Journey 底下有很多 Chapter 所以為單向複合關聯，Journey必須要知道自己底下有多少Chapter
//Since there are multiple Chapters under Journey, it forms a unidirectional composition association.
//Journey needs to be aware of how many Chapters it contains.

class Journey
{
private:
    std::string name;
    std::string description;
    int price;
    std::vector<Chapter*> chapters;
public:
    Journey(std::string name,std::string description,int price,
            std::vector<Chapter*> chapters)
        {
            this->SetName(name);
            this->SetDescription(description);
            this->SetPrice(price);
            this->SetChapters(chapters);
        }
    ~Journey(){};


    //TODO : Student Join to this Journey

    //getter
    std::string GetName();
    std::string GetDescription();
    int GetPrice();
    std::vector<Chapter*> GetChapters();

    //setter
    void SetName(std::string name);
    void SetDescription(std::string description);
    void SetPrice(int price);
    void SetChapters(std::vector<Chapter*> chapter);
};

std::string Journey::GetName()
{
    return this->name;
}

std::string Journey::GetDescription()
{
    return this->description;
}

int Journey::GetPrice()
{
    return this->price;
}

std::vector<Chapter*> Journey::GetChapters()
{
    return this->chapters;
}

void Journey::SetName(std::string name)
{
    utils::LengthShouldBe(name,1,30);
    this->name = name;
}

void Journey::SetDescription(std::string description)
{
    utils::LengthShouldBe(description,0,300);
    this->description = description;
}

void Journey::SetPrice(int price)
{
    utils::ValShouldBigger(price,1);
    this->price = price;
}

void Journey::SetChapters(std::vector<Chapter*> chapter)
{
    utils::SizeShouldBigger(chapter,0);
    this->chapters = chapter;
}

#endif
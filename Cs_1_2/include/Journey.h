#pragma once
#ifndef _JOURNEY_H_
#define _JOURNEY_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "../include/utils/utils.h"
// #include "Chapter.h"


class Chapter;

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
            std::vector<Chapter*> chapters);
        // {
        //     this->SetName(name);
        //     this->SetDescription(description);
        //     this->SetPrice(price);
        //     this->SetChapters(chapters);
        // }
    ~Journey();


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



#endif
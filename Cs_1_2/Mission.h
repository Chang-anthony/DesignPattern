#pragma once
// #ifndef _MISSION_H_
// #define _MISSION_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "include/utils.h"
#include "CheckMissionState.h"
#include "Challenge.h"
#include "Scene.h"

// Forward declaration
// class Challenge;
// class Scene;

//Mission為在Chapter 底下中的其中一個，他不能單獨存在在 Chapter 之外 及單向複合關聯(A One-Way Composition Association)
//所以Mission不須知道他在哪個Chapter 底下
// Mission is one of the components under Chapter. It cannot exist independently outside of Chapter.
// This forms a one-way composition association, meaning Mission does not need to be aware of which Chapter it belongs to.

class Mission
{
private:
    /* data */
    int id;
    std::string name;
    Challenge* challenge;
    std::vector<Scene*> scenes;
public:
    Mission(){}
    Mission(int id,std::string name,Challenge* challenge,std::vector<Scene*> scenes)
    {
        SetID(id);
        SetName(name);
        SetChallenge(challenge);
        SetScenes(scenes);
    };
    ~Mission(){};

    int ExpAward();

    //getter
    int GetID();
    std::string GetName();
    Challenge* GetChallenge();
    std::vector<Scene*> GetScenes();

    //setter
    void SetID(int id);
    void SetName(std::string name);
    void SetChallenge(Challenge* challenge);
    void SetScenes(std::vector<Scene*> scenes);

};

int Mission::ExpAward()
{
    int exp = 0;
    for(auto scene:scenes)
        exp += scene->ExpAward();  
    return exp;
}

int Mission::GetID()
{
    return this->id;
}

std::string Mission::GetName()
{
    return this->name;
}

Challenge* Mission::GetChallenge()
{
    return this->challenge;
}

std::vector<Scene*> Mission::GetScenes()
{
    return this->scenes;
}

void Mission::SetID(int id)
{
    utils::ValShouldBigger(id,0);
    this->id = id;
}

void Mission::SetName(std::string name)
{
    utils::LengthShouldBe(name,1,30);
    this->name = name;
}

void Mission::SetChallenge(Challenge* Challenge)
{
    utils::RequireNonNull(challenge);
    this->challenge = challenge;
}

void Mission::SetScenes(std::vector<Scene*> scenes)
{
    utils::SizeShouldBigger(scenes,0);
    this->scenes = scenes;
}

// #endif // __MISSION_H__
#pragma once
// #ifndef _MISSION_H_
// #define _MISSION_H_
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "../include/utils/utils.h"

// Forward declaration
class Challenge;
class Scene;

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
    Mission(int id,std::string name,Challenge* challenge,const std::vector<Scene*> &scenes);
    ~Mission();
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
    void SetScenes(const std::vector<Scene*>& scenes);

};



// #endif // __MISSION_H__
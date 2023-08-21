#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "../include/utils/utils.h"

class Scene //AbstractClass
{
private:
    /* data */
    int id;
    std::string name;
public:
    Scene(int id,std::string name);
    // {
    //     SetID(id);
    //     SetName(name);
    // };
    ~Scene();

    virtual int ExpAward() = 0;//need to initial 

    //getter
    int GetID();
    std::string GetName();

    //setter
    void SetID(int id);
    void SetName(std::string name);
};




#endif // SCENE_H
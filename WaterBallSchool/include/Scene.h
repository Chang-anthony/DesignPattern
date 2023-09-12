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
    int exp;
    std::string name;
public:
    Scene(int id,std::string name,int exp);
    ~Scene();

    virtual int ExpAward() = 0;//need to initial 

    //getter
    int GetID();
    int GetExp();
    std::string GetName();

    //setter
    void SetID(int id);
    void SetName(std::string name);
    void SetExp(int exp);
};

#endif // SCENE_H
#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "include/utils.h"

class Scene //AbstractClass
{
private:
    /* data */
    int id;
    std::string name;
public:
    Scene(int id,std::string name)
    {
        SetID(id);
        SetName(name);
    };
    ~Scene(){};

    virtual int ExpAward() = 0;//need to initial 

    //getter
    int GetID();
    std::string GetName();

    //setter
    void SetID(int id);
    void SetName(std::string name);
};



int Scene::GetID()
{
    return id;
}

std::string Scene::GetName()
{
    return name;
}

void Scene::SetID(int id)
{
    utils::ValShouldBigger(id,0);
    this->id = id;
}


void Scene::SetName(std::string name)
{
    utils::LengthShouldBe(name,1,30);
    this->name = name;
}

#endif // SCENE_H
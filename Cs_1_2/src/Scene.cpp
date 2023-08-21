#include "../include/Scene.h"


Scene::Scene(int id,std::string name,int exp)
{
    SetID(id);
    SetName(name);
    SetExp(exp);
}


int Scene::GetID()
{
    return id;
}

int Scene::GetExp()
{
    return this->exp;
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
    utils::LengthShouldBe(name,1,50);
    this->name = name;
}

void Scene::SetExp(int exp)
{
    utils::ValShouldBigger(exp,0);
    this->exp = exp;
}

Scene::~Scene()
{
    
}

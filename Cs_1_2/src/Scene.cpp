#include "../include/Scene.h"


Scene::Scene(int id,std::string name)
{
    SetID(id);
    SetName(name);
}


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

Scene::~Scene()
{
    
}

#pragma once
#ifndef _CONTENTSCENE_H_
#define _CONTENTSCENE_H_
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "../include/utils/utils.h"
#include "../include/Scene.h"


class ContentScene : public Scene
{
private:
    /* data */
public:
    //Derived class constructor
    ContentScene(int id,std::string name,int exp);
    ~ContentScene();

    int ExpAward() override; 
};





#endif // CONTENTSCENE_H
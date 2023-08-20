#pragma once
#ifndef _CONTENTSCENE_H_
#define _CONTENTSCENE_H_
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "include/utils.h"
#include "Scene.h"


class ContentScene : public Scene
{
private:
    /* data */
public:
    //Derived class constructor
    ContentScene(int id,std::string name):Scene(id,name){};
    ~ContentScene(){};

    int ExpAward() override; 
};


int ContentScene::ExpAward() 
{
    return 1000 * 1.1;
}


#endif // CONTENTSCENE_H
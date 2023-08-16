#ifndef CONTENTSCENE_H
#define CONTENTSCENE_H
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "include/utils.h"
#include "Scene.h"


class ContentScene : Scene
{
private:
    /* data */
public:
    //Derived class constructor
    ContentScene(int id,int name):Scene(id,name){};
    ~ContentScene(){};

    int ExpAward() override; 
};


int ContentScene::ExpAward() 
{
    return 1000 * 1.1;
}


#endif // CONTENTSCENE_H
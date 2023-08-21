#include "../include/ContentScene.h"


ContentScene::ContentScene(int id,std::string name):Scene(id,name)
{

}


int ContentScene::ExpAward() 
{
    return 1000 * 1.1;
}

ContentScene::~ContentScene()
{

}
#include "../include/ContentScene.h"


ContentScene::ContentScene(int id,std::string name,int exp):Scene(id,name,exp)
{

}


int ContentScene::ExpAward() 
{
    return this->GetExp() * 1.3;
}

ContentScene::~ContentScene()
{

}
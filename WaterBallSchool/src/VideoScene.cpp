#include "../include/VideoScene.h"

VideoScene::VideoScene(int id,std::string name,int exp):Scene(id,name,exp)
{

}

VideoScene::~VideoScene()
{

}

int VideoScene::ExpAward()
{
    return this->GetExp() * 1.5;
}
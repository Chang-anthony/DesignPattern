#include "../include/VideoScene.h"

VideoScene::VideoScene(int id,std::string name):Scene(id,name)
{

}

VideoScene::~VideoScene()
{

}

int VideoScene::ExpAward()
{
    return 1000 * 1.5;
}
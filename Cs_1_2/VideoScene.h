#ifndef VIDEOSCENE_H
#define VIDEOSCENE_H
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "include/utils.h"
#include "Scene.h"

//need to public so the List can transform videoscene to father class scene
class VideoScene : public Scene
{
private:
    /* data */
public:
    VideoScene(int id,std::string name):Scene(id,name){};
    ~VideoScene(){};

    int ExpAward() override;
    // or
    // int ExpAward() override
    // {
    //     return 1000 * 1.5;
    // }

};

int VideoScene::ExpAward()
{
    return 1000 * 1.5;
}

#endif // VIDEOSCENE_H
#pragma once
#ifndef _VIDEOSCENE_H_
#define _VIDEOSCENE_H_
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "../include/utils/utils.h"
#include "../include/Scene.h"


//need to public so the List can transform videoscene to father class scene
class VideoScene : public Scene
{
private:
    /* data */
public:
    VideoScene(int id,std::string name,int exp);
    ~VideoScene();
    int ExpAward() override;

};

#endif // VIDEOSCENE_H
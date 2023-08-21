/*
* @author - (Anthony)
*/
#include <iostream>
#include <stdio.h>
#include "Challenge.h"
#include "Student.h"
#include "Mission.h"
#include "CheckMissionState.h"
#include "VideoScene.h"
#include "ContentScene.h"



int main()
{
    std::vector<CheckMissionState*> missioncarryon = std::vector<CheckMissionState*>();
    std::vector<Scene*> scenes
    {
        new VideoScene(3,"456"),
        new ContentScene(4,"789"),
    };
    // VideoScene* video = new VideoScene(3,"456");
    // ContentScene* content =  new ContentScene(4,"789");
    // std::vector<Scene*> scenes = std::vector<Scene*>();
    // scenes.push_back(video);
    // scenes.push_back(content);

    std::cout << missioncarryon.size() << std::endl;
    Student anthony = Student("Anthony","123545",missioncarryon);
    Mission* test = new Mission(1,"test",new Challenge(1,"test_challenge"),scenes);
    CheckMissionState* testmissionstate = anthony.CarryMission(test);
    testmissionstate->CompleteMission();
    //VideoScene(1,"123");
    //test.GainExp(3000);
    return 0;
}
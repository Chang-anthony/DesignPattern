/*
* @author - (Anthony)
*/
#include <iostream>
#include <stdio.h>
#include "../include/Student.h"
#include "../include/Mission.h"
#include "../include/CheckMissionState.h"
#include "../include/VideoScene.h"
#include "../include/ContentScene.h"
#include "../include/Challenge.h"



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

    // Challenge* challenge = new Challenge(2,"test2");

    // std::cout << "test" << " ด๚ธี" << std::endl;
    Student anthony = Student("Anthony","123545",missioncarryon);
    Mission* test = new Mission(1,"test",new Challenge(2,"test2"),scenes);
    CheckMissionState* testmissionstate = anthony.CarryMission(test);
    testmissionstate->CompleteMission();
    //VideoScene(1,"123");
    //test.GainExp(3000);
    return 0;
}
/*
* @author - (Anthony)
*/
#include <iostream>
#include <stdio.h>
#include "include/utils.h"
#include "LevelSheet.h"
#include "Student.h"
#include "Journey.h"
#include "Chapter.h"
#include "Mission.h"
#include "Challenge.h"
#include "Scene.h"
#include "VideoScene.h"
#include "ContentScene.h"
#include "CheckMissionState.h"


int main()
{
    std::cout <<"hello world!!!" << std::endl;
    // int* object = 0;
    // requireNonNull(object);
    std::string str = "1654135135";
    //lengthshouldBe(str,1,5);
    std::vector<CheckMissionState*> missioncarryon = std::vector<CheckMissionState*>();
    std::vector<Scene*> scenes = std::vector<Scene*>()
    {
        new VideoScene(3,"456"),
        new ContentScene(4,"789"),   
    };
    std::cout << missioncarryon.size() << std::endl;
    Student test = Student("Anthony","123545",missioncarryon);
    Mission* test = new Mission(1,"test",new Challenge(1,"test_challenge"),scenes);
    VideoScene(1,"123");
    // test.GainExp(3000);
    return 0;
}
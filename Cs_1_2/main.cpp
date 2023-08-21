/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "../include/Student.h"
#include "../include/Mission.h"
#include "../include/CheckMissionState.h"
#include "../include/VideoScene.h"
#include "../include/ContentScene.h"
#include "../include/Challenge.h"
#include "../include/Adventurer.h"
#include "../include/Journey.h"
#include "../include/Chapter.h"
#include "../include/TourGroup.h"



int main()
{
    std::vector<CheckMissionState*> missioncarryon = std::vector<CheckMissionState*>();
    // std::vector<Scene*> scenes
    // {
    //     new VideoScene(3,"456"),
    //     new ContentScene(4,"789"),
    // };

    std::vector<Scene*> testtwo = std::vector<Scene*>();

    Mission* test = new Mission(1,"test",new Challenge(2,"test2"),testtwo);

    std::string str = "物件導向的新手村";
    // std::wstring str = L"物件導向不新手的新手村";//中文字為寬字元所以現在使用的可能長度都要使用此解法

    // 開設旅程
    Journey* designPattern = new Journey("軟體設計模式精通之旅","我們只做最好的內容。",6999,{
        new Chapter(1,str
                    ,{new Mission(1,"OOA｜建出你的領域模型吧！",
                        new Challenge(1,"一起建出領域模型吧！"),
                            std::vector<Scene*>
                            {
                                new VideoScene(1,"設計模式之旅展開冒險吧！",300),
                                new VideoScene(2,"這個世界正是物件導向的",500),
                                new VideoScene(3,"物件 vs. 類別",500),
                                new VideoScene(4,"類別的關係 (Relationship)",600)
                            }),
                    }),
        },std::vector<Adventurer*>(),std::vector<TourGroup*>());

    

    Student* anthony = new Student("Anthony","123545",std::vector<CheckMissionState*>(),std::vector<Adventurer*>());
    Adventurer* adventurer = designPattern->Join(anthony);
    TourGroup* tourGroup = adventurer->GetTourGroup();
    std::vector<Adventurer*> adventurers = tourGroup->GetAdventurers(); 

    // 查看學員目前正在執行的第一項任務
    CheckMissionState* testmissionstate = anthony->GetMissionState()[0];
    std::cout << "學員 " << anthony->GetAccount() << "正在執行任務 "<< testmissionstate->GetMission()->GetName() << std::endl;
    // 完成這項任務
    testmissionstate->CompleteMission();

    //VideoScene(1,"123");
    //test.GainExp(3000);
    return 0;
}
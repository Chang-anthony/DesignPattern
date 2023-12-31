#ifndef _CHAPTER_H_
#define _CHAPTER_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "../include/utils/utils.h"
// #include "Mission.h"

class Mission;

//Chapter為在Journey 底下中的其中一個，他不能單獨存在在 Journey 之外
//所以Chapter為包含在Journey 所以為單向複合關聯，他不需要知道自己在哪個Journey底下所以並不需宣告
// Chapter is one of the components under Journey. It cannot exist independently outside of Journey.
// Therefore, Chapter is included within Journey, making it a unidirectional composition association.
// Since Chapter does not need to be aware of which specific Journey it belongs to, there is no need to declare it.


//Chapter 裡包含許多Mission 所以 Chapter 與 Mission 也為單向複合關聯，Chapter必須要知道自己底下有多少Mission
//Since Chapter contains numerous Missions, the relationship between Chapter and Mission is also a unidirectional composition association.
//Chapter needs to be aware of how many Missions it encompasses.

class Chapter
{
private:
    int id;
    std::string name;
    std::vector<Mission*> missions;
public:
    Chapter(int id,std::string name,std::vector<Mission*> missions);
    ~Chapter();

    // 提供一些好用的方法：拿第一個任務
    Mission* GetFirstMission();

    //getter
    int GetID();
    std::string GetName();
    std::vector<Mission*> GetMissions();

    //setter
    void SetID(int id);
    void SetName(std::string name);
    void SetMissions(std::vector<Mission*> missions);

};



#endif
#include "../include/Mission.h"
#include "../include/Scene.h"
#include "../include/Challenge.h"


Mission::Mission(int id,std::string name,Challenge* challenge,const std::vector<Scene*> &scenes)
{
    SetID(id);
    SetName(name);
    SetChallenge(challenge);
    SetScenes(scenes);
}

int Mission::ExpAward()
{
    int exp = 0;
    for(auto scene:scenes)
        exp += scene->ExpAward();  
    return exp;
}

int Mission::GetID()
{
    return this->id;
}

std::string Mission::GetName()
{
    return this->name;
}

Challenge* Mission::GetChallenge()
{
    return this->challenge;
}

std::vector<Scene*> Mission::GetScenes()
{
    return this->scenes;
}

void Mission::SetID(int id)
{
    utils::ValShouldBigger(id,0);
    this->id = id;
}

void Mission::SetName(std::string name)
{
    utils::LengthShouldBe(name,1,50);
    this->name = name;
}

void Mission::SetChallenge(Challenge* challenge)
{
    utils::RequireNonNull(challenge);
    this->challenge = challenge;
}

void Mission::SetScenes(const std::vector<Scene*> &scenes)
{

    utils::RequireNonNull(&scenes);
    this->scenes = scenes;
}

Mission::~Mission()
{
    
}
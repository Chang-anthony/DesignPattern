#include "../include/Mission.hpp"
#include "../include/Scene.hpp"
#include "../include/Challenge.hpp"

Mission::Mission(/* args */)
{
    this->scenes = std::set<Scene*>();
    this->challenge = std::set<Challenge*>();

}

void Mission::AddChallenge(Challenge* challenge)
{  
    this->challenge.insert(challenge);
}

void Mission::AddScene(Scene* scene)
{
    this->scenes.insert(scene);
}

Mission::~Mission()
{
}
#ifndef _MISSION_H_
#define _MISSION_H_

#include <iostream>
#include <set>
#include <vector>

class Scene;
class Challenge;

class Mission
{
private:
    /* data */
    std::set<Scene*> scenes;
    std::set<Challenge*> challenge;
public:
    Mission(/* args */);
    ~Mission();

    void AddScene(Scene* scene);
    void AddChallenge(Challenge* challenge);
};

#endif /* _MISSION_H_ */

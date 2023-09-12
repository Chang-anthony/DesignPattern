#ifndef _WORLD_H_
#define _WORLD_H_

#include <iostream>
#include <set>
#include <vector>

class Adventurer;

class World
{
private:
    /* data */
    std::set<Adventurer*> adventurers;
public:
    World(/* args */);
    ~World();

    void AddAdventurer(Adventurer* adventurer);
    void MoveForward(Adventurer* adventurer,int steps);
};

#endif /* _WORLD_H_ */

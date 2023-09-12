#include "../include/Adventurer.hpp"
#include "../include/World.hpp"

World::World(/* args */)
{
   adventurers = std::set<Adventurer*>();
}

void World::AddAdventurer(Adventurer* adventurer)
{
    adventurers.insert(adventurer);
}

void World::MoveForward(Adventurer* adventurer,int steps)
{
    std::cout << "adventurer Move forward " <<  steps << std::endl;
    adventurer->AddStep(steps);
}

World::~World()
{
}
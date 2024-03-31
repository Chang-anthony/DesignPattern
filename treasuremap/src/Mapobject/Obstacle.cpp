#include <Coord.hpp>
#include <Obstacle.hpp>

Obstacle::Obstacle(Coord* pos) : Mapobject('o', pos)
{
}

Obstacle::~Obstacle()
{
}
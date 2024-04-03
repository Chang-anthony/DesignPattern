#include <Coord.hpp>
#include <Obstacle.hpp>
#include <Adventure.hpp>

Obstacle::Obstacle(Coord* pos, Adventure* game) : Mapobject("o", pos, game)
{
}

Obstacle::~Obstacle()
{
}
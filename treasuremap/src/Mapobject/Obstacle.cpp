#include <Coord.hpp>
#include <Obstacle.hpp>
#include <Adventure.hpp>

Obstacle::Obstacle(Coord* pos, Adventure* game) : Mapobject("o", pos, game)
{
}

Obstacle* Obstacle::genObstacle(Coord* newPos, Adventure* game)
{
    return new Obstacle(newPos, game);
}

void Obstacle::move(int x, int y)
{
    return;
}

Obstacle::~Obstacle()
{
}
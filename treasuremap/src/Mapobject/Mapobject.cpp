#include <Mapobject.hpp>
#include <Coord.hpp>
#include <Adventure.hpp>
#include <utils.h>
#include <Treasure.hpp>
#include <Monster.hpp>
#include <Obstacle.hpp>

Mapobject::Mapobject(std::string symbol, Coord* pos, Adventure* game)
{
    SetSymbol(symbol);
    SetCoord(pos);
    setAdventure(game);
}

bool Mapobject::IsNearBy(Mapobject* other)
{
    if(this->GetCoord()->distance(other->GetCoord()) <= 1.0)
        return true;
    else
        return false;
}

Mapobject* Mapobject::GenObj(Adventure* game, std::string target)
{
    Coord* newPos = Coord::RandomCoord(game->GetBoundX(), game->GetBoundY());
    while (true) {
        if(game->IsNullObj(newPos))
            break;
        newPos = Coord::RandomCoord(game->GetBoundX(), game->GetBoundY());
    }

    if(target == "M") {
        return Monster::genMonster(newPos, game);
    }
    else if (target == "o") {
        return Obstacle::genObstacle(newPos, game);
    }
    else {
        return Treasure::genTreasure(newPos, game);
    }
}

std::string Mapobject::GetSymbol()
{
    return this->symbol;
}

Coord* Mapobject::GetCoord()
{
    return this->pos;
}

Adventure* Mapobject::GetGame()
{
    return this->game;
}

void Mapobject::SetSymbol(std::string symbol)
{
    this->symbol = symbol;
}

void Mapobject::SetCoord(int x, int y)
{
    this->pos = new Coord(x, y);
}

void Mapobject::SetCoord(Coord* coord)
{
    this->pos = utils::RequireNonNull(coord);
}

void Mapobject::setAdventure(Adventure* game)
{
    this->game = utils::RequireNonNull(game);
}

Mapobject::~Mapobject()
{
}
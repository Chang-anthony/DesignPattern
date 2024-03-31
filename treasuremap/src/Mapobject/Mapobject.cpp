#include <Mapobject.hpp>
#include <Coord.hpp>
#include <Adventure.hpp>
#include <utils.h>

Mapobject::Mapobject(char symbol, Coord* pos, Adventure* game)
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

char Mapobject::GetSymbol()
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

void Mapobject::SetSymbol(char symbol)
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
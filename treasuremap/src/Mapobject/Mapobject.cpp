#include <Mapobject.hpp>
#include <Coord.hpp>

Mapobject::Mapobject(char symbol, Coord* pos) : symbol(symbol), pos(pos)
{
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
    this->pos = coord;
}

Mapobject::~Mapobject()
{
}
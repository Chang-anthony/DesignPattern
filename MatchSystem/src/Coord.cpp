#include "../include/Coord.hpp"

Coord::Coord(int x, int y)
{
    SetX(x);
    SetY(y);
}

int Coord::GetX()
{
    return this->x;
}

int Coord::GetY()
{
    return this->y;
}

void Coord::SetX(int x)
{
    this->x = x;
}

void Coord::SetY(int y)
{
    this->y = y;
}

Coord::~Coord()
{

}

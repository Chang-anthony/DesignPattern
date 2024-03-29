#include <Coord.hpp>
#include <math.h>


Coord::Coord(int x, int y): x(x), y(y)
{
}

double Coord::distance(Coord *coord)
{
    double sum = (this->x - coord->x) * (this->x - coord->x) + (this->y - coord->y) * (this->y - coord->y);
    return sqrt(sum);
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
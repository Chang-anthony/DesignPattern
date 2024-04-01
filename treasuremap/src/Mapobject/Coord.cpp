#include <Coord.hpp>
#include <math.h>
#include <random>


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

Coord* Coord::RandomCoord(int boundx, int boundy)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> disx(0, boundx); // 0 到 10 的随机整数
    std::uniform_int_distribution<int> disy(0, boundy); // 0 到 10 的随机整数

    int x = disx(gen);
    int y = disy(gen);
    Coord* pos = new Coord(x, y);

    return pos;
}

Coord::~Coord()
{
}
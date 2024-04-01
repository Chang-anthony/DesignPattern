#include "Adventure.hpp"
#include <random>
#include <Coord.hpp>
#include <utils.h>
#include <Mapobject.hpp>
#include <vector>
#include <Charator.hpp>

//TODO

Adventure::Adventure(Charator* charactor)
{
    this->objs = std::vector<std::vector<Mapobject*>>(boundx, std::vector<Mapobject*>(boundy, nullptr));
    SetCharator(charactor);
}

Coord* Adventure::RandomCoord()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> disx(0, boundx); // 0 到 10 的随机整数
    std::uniform_int_distribution<int> disy(0, boundy); // 0 到 10 的随机整数

    int x = disx(gen);
    int y = disy(gen);
    Coord* pos = new Coord(x, y);

    if(IsNullObj(pos))
        return pos;
    else
        return RandomCoord();
}

bool Adventure::IsNullObj(Coord* pos)
{
    return !objs[pos->GetX()][pos->GetY()];
}

Charator* Adventure::GetCharator()
{
    return charactor;
}

void Adventure::SetCharator(Charator* charactor)
{
    this->charactor = utils::RequireNonNull(charactor);
}

Adventure::~Adventure()
{
}
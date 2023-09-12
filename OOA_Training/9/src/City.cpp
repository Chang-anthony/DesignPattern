#include "../include/Road.hpp"
#include "../include/City.hpp"



City::City(/* args */)
{
    this->roads = std::set<Road*>();
}

Road* City::Connect(City* city)
{
    Road* road = new Road(this,city);
    //加入A與B市的雙向關聯
    city->roads.insert(road);
    this->roads.insert(road);

    return road;
}

City::~City()
{
}
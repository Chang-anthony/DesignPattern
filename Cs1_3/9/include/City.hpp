#ifndef _CITY_H_
#define _CITY_H_

#include <iostream>
#include <set>
#include <vector>

class Road;

class City
{
private:
    /* data */
    std::set<Road*> roads;
public:
    City(/* args */);
    ~City();

    Road* Connect(City* city);
};




#endif /* _CITY_H_ */

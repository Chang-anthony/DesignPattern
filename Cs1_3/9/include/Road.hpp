#ifndef _ROAD_H_
#define _ROAD_H_

#include <iostream>

class City;

class Road
{
private:
    City* A;
    City* B;
public:
    Road(City* A ,City* B);
    ~Road();
};




#endif /* _ROAD_H_ */

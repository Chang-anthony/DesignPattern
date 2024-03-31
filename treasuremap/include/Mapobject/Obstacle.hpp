#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include <iostream>
#include "Mapobject.hpp"

class Coord;

class Obstacle : public Mapobject
{
private:
    /* data */
public:
    Obstacle(Coord* pos);
    ~Obstacle();
};

#endif /* _OBSTACLE_H_ */

#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include <iostream>
#include "Mapobject.hpp"

class Coord;
class Adventure;

class Obstacle : public Mapobject
{
private:
    /* data */
public:
    Obstacle(Coord* pos, Adventure* game);
    ~Obstacle();
};

#endif /* _OBSTACLE_H_ */

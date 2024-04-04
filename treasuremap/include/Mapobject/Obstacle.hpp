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

    void move(int x, int y) override;
    static Obstacle* genObstacle(Coord* newPos, Adventure* game);
};

#endif /* _OBSTACLE_H_ */

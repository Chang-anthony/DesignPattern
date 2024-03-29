#ifndef _COORD_H_
#define _COORD_H_

#include <iostream>

class Coord
{
private:
    /* data */
    int x;
    int y;
public:
    Coord(int x, int y);
    ~Coord();

    double distance(Coord* coord);

    //
    int GetX();
    int GetY();

    void SetX(int x);
    void SetY(int y);
};

#endif /* _COORD_H_ */

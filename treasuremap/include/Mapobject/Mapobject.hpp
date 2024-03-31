#ifndef _MAPOBJECT_H_
#define _MAPOBJECT_H_

#include <iostream>

class Coord;

class Mapobject
{
private:
    /* data */
    char symbol;
    Coord* pos;
public:
    Mapobject(char symbol, Coord* pos);
    ~Mapobject();

    //TODO:
    bool IsNearBy(Mapobject* other);
    static Mapobject* GenObj();
    virtual void move(int x, int y) = 0;

    char GetSymbol();
    Coord* GetCoord();

    void SetSymbol(char symbol);
    void SetCoord(int x, int y);
    void SetCoord(Coord* coord);
};

#endif /* _MAPOBJECT_H_ */

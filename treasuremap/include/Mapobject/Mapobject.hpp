#ifndef _MAPOBJECT_H_
#define _MAPOBJECT_H_

#include <iostream>

class Coord;
class Adventure;

class Mapobject
{
private:
    /* data */
    char symbol;
    Coord* pos;
    Adventure* game;
public:
    Mapobject(char symbol, Coord* pos, Adventure* game);
    ~Mapobject();

    //TODO:
    bool IsNearBy(Mapobject* other);
    static Mapobject* GenObj(Adventure* game);
    virtual void move(int x, int y) = 0;

    char GetSymbol();
    Coord* GetCoord();
    Adventure* GetGame();

    void SetSymbol(char symbol);
    void SetCoord(int x, int y);
    void SetCoord(Coord* coord);
    void setAdventure(Adventure* game);
};
#endif /* _MAPOBJECT_H_ */

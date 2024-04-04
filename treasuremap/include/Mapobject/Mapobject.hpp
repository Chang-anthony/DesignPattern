#ifndef _MAPOBJECT_H_
#define _MAPOBJECT_H_

#include <iostream>

class Coord;
class Adventure;

class Mapobject
{
private:
    /* data */
public:
    Mapobject(std::string symbol, Coord* pos, Adventure* game);
    ~Mapobject();

    //TODO:
    bool IsNearBy(Mapobject* other);
    static Mapobject* GenObj(Adventure* game, std::string target);
    virtual void move(int x, int y) = 0;

    std::string GetSymbol();
    Coord* GetCoord();
    Adventure* GetGame();

    void SetSymbol(std::string symbol);
    void SetCoord(int x, int y);
    void SetCoord(Coord* coord);
    void setAdventure(Adventure* game);
protected:
    std::string symbol;
    Coord* pos;
    Adventure* game;
};
#endif /* _MAPOBJECT_H_ */

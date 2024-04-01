#ifndef _ADVENTURE_H_
#define _ADVENTURE_H_

#include <iostream>
#include <vector>
#include <string>

class Mapobject;
class Round;
class Charator;
class Coord;

class Adventure
{
private:
    std::vector<std::vector<Mapobject*>> objs;
    Charator* charactor;
public:
    Adventure();
    Adventure(Charator* charator);
    ~Adventure();

    //function
    void GameStart();
    void remove(Mapobject* obj);
    static Adventure* newGame();
    bool IsNullObj(Coord* pos);

    //getter
    Charator* GetCharator();
    int GetBoundX();
    int GetBoundY();
    //setter
    void SetCharator(Charator* charator);

protected:
    static const int boundx = 10;
    static const int boundy = 10;

    void touched(Mapobject* obj1, Mapobject* obj2);
    bool isEnd();
    Round* startRound();
    void GameEnd();
    static Mapobject* RandomGenObj(Adventure* game);
    static Adventure*  RandChartorCoord(Adventure* game);
};

#endif /* _ADVENTURE_H_ */

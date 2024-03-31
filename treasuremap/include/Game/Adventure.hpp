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
    Adventure(Charator* charactor);
    ~Adventure();

    //function
    void GameStart();
    void remove(Mapobject* obj);
    Adventure newGame();
    bool isHaveObj(Coord* pos);

protected:
    void touched(Mapobject* obj1, Mapobject* obj2);
    bool isEnd();
    Round* startRound();
    void GameEnd();
};

#endif /* _ADVENTURE_H_ */

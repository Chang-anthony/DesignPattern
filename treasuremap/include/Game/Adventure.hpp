#ifndef _ADVENTURE_H_
#define _ADVENTURE_H_

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class Mapobject;
class Round;
class Charator;
class Coord;

class Adventure
{
private:
    const std::unordered_map<int, std::string> dirmap = {
        {0, "↑"},
        {1, "→"},
        {2, "↓"},
        {3, "←"},
    };

    const std::unordered_map<std::string, std::pair<int, int>> dirTopos = {
        {"↑", {0, 1}},
        {"→", {0, -1}},
        {"↓", {-1, 0}},
        {"←", {1, 0}},
    };

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
    std::vector<std::vector<Mapobject*>> GetObjs();
    Charator* GetCharator();
    int GetBoundX();
    int GetBoundY();
    //setter
    void SetCharator(Charator* charator);
    std::string GetChooseSymbol(int choose);
    std::pair<int, int> GetDirPos(int choose);
    bool IsOutBound(Coord* pos, std::pair<int, int> dpos);

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

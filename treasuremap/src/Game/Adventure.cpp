#include "Adventure.hpp"
#include <random>
#include <Coord.hpp>
#include <utils.h>
#include <Mapobject.hpp>
#include <vector>
#include <Charator.hpp>

//TODO

Adventure::Adventure()
{
    this->objs = std::vector<std::vector<Mapobject*>>(boundx, std::vector<Mapobject*>(boundy, nullptr));
}

Adventure::Adventure(Charator* charator)
{
    this->objs = std::vector<std::vector<Mapobject*>>(boundx, std::vector<Mapobject*>(boundy, nullptr));
    SetCharator(charactor);
}

void Adventure::GameStart()
{
    std::cout << "冒險遊戲開始" << std::endl;
    Adventure* newGame = Adventure::newGame();

    
}

Adventure* Adventure::newGame()
{   
    Adventure* game = new Adventure();
    Charator* charator = new Charator(new Coord(0, 0), game);
    game->SetCharator(charator);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(10, 15);

    int randomNumber = distribution(gen);

    int count = 0;
    while (count < randomNumber) {
        Mapobject* gens = Adventure::RandomGenObj(game);
        if(game->IsNullObj(gens->GetCoord())) {
            int x = gens->GetCoord()->GetX();
            int y = gens->GetCoord()->GetY();
            game->objs[x][y] = gens;
            count++;
        }
    }
    
    return Adventure::RandChartorCoord(game);
}

bool Adventure::IsOutBound(Coord* pos, std::pair<int, int> dpos)
{   
    int newX = pos->GetX() + dpos.first;
    int newY = pos->GetY() + dpos.second;

    bool flag = false;
    flag = (newX >= 0) && (newX < boundx) && ( newY >= 0) && (newY < boundy);

    return flag;
}

void Adventure::remove(Mapobject* obj)
{
    int x = obj->GetCoord()->GetX();
    int y = obj->GetCoord()->GetY();

    objs[x][y] = nullptr;
}

std::string Adventure::GetChooseSymbol(int choose)
{
    auto it = dirmap.find(choose);
    return it->second;
}

std::pair<int, int> Adventure::GetDirPos(int choose)
{
    auto it = dirmap.find(choose);
    std::string dir = it->second;
    return dirTopos.find(dir)->second;
}

//Gen Monster and treasure and obstacle
Mapobject* Adventure::RandomGenObj(Adventure* game)
{   
    Mapobject* obj = Mapobject::GenObj(game);
    return obj;
}

Adventure* Adventure::RandChartorCoord(Adventure* game)
{
    Coord* pos = Coord::RandomCoord(game->boundx, game->boundy);
    if(game->IsNullObj(pos)) {
        game->charactor->SetCoord(pos);
        return game;
    }
    else
        return Adventure::RandChartorCoord(game);
    
}

bool Adventure::IsNullObj(Coord* pos)
{
    return !objs[pos->GetX()][pos->GetY()];
}

std::vector<std::vector<Mapobject*>> Adventure::GetObjs()
{
    return objs;
}

Charator* Adventure::GetCharator()
{
    return charactor;
}

int Adventure::GetBoundX()
{
    return boundx;
}

int Adventure::GetBoundY()
{
    return boundy;
}

void Adventure::SetCharator(Charator* charactor)
{
    this->charactor = utils::RequireNonNull(charactor);
}

Adventure::~Adventure()
{
}
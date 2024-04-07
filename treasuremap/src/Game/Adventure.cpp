#include "Adventure.hpp"
#include <random>
#include <Coord.hpp>
#include <utils.h>
#include <Mapobject.hpp>
#include <vector>
#include <Charator.hpp>
#include <TouchedHandler.hpp>
#include <RoleObstacleTouched.hpp>
#include <RoleTreasureTouched.hpp>
#include <Round.hpp>
#include <map>


Adventure::Adventure()
{
    this->handler = new RoleObstacleTouched(new RoleTreasureTouched(nullptr, this), this);
    this->objs = std::vector<std::vector<Mapobject*>>(boundx, std::vector<Mapobject*>(boundy, nullptr));
}

Adventure::Adventure(Charator* charator)
{   
    this->handler = new RoleObstacleTouched(new RoleTreasureTouched(nullptr, this), this);
    this->objs = std::vector<std::vector<Mapobject*>>(boundx, std::vector<Mapobject*>(boundy, nullptr));
    SetCharator(charactor);
}

void Adventure::GameStart()
{
    std::cout << "冒險遊戲開始" << std::endl;
    Adventure* newGame = Adventure::newGame();
    
    Round* newRound = newGame->startRound();


    while (!newGame->isEnd())
    {
        newRound->run();
        newRound = newGame->startRound();
    }

    newGame->GameEnd();
}

Round* Adventure::startRound()
{
    return new Round(this);
}

bool Adventure::isEnd()
{
    int CharatorHp = charactor->GetHp();

    bool haveMonster = false;
    for (auto mons: objs) {
        for (auto obj : mons){
            if(obj && obj->GetSymbol() == "M") {
                haveMonster = true;
                break;
            }
        }
    }

    return !(haveMonster) || (CharatorHp <= 0);
}

void Adventure::GameEnd()
{
    int CharatorHp = charactor->GetHp();
    if(CharatorHp > 0)
        std::cout << "恭喜玩家贏得冒險遊戲的勝利!!!" << std::endl;
    else
        std::cout << "非常可惜,這場遊戲玩家以死亡!!!" << std::endl;
}

Adventure* Adventure::newGame()
{   
    Adventure* game = new Adventure();
    Charator* charator = new Charator(new Coord(0, 0), game);
    game->SetCharator(charator);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(10, 15);
    std::uniform_int_distribution<int> genchoice(0, 2);

    int randomNumber = distribution(gen);
    std::vector<std::string> targets = {"M", "o", "X"};
    std::vector<int> targets_count = {5, 5, 5};
    std::map<int, std::vector<Mapobject*>> store = {
        {0, std::vector<Mapobject*>()},
        {1, std::vector<Mapobject*>()},
        {2, std::vector<Mapobject*>()},
    };

    int count = 0;
    int gens_count = 0;
    while (count < randomNumber) {
        while (gens_count < 3) {
            Mapobject* gens = Adventure::RandomGenObj(game, targets[gens_count]);
            if(game->IsNullObj(gens->GetCoord())) {
                int x = gens->GetCoord()->GetX();
                int y = gens->GetCoord()->GetY();
                game->SetObj(gens);
                count++;
                store[gens_count].push_back(gens);
                if(store[gens_count].size() >= targets_count[gens_count])
                    gens_count++;
            }
        }
    }
    
    return Adventure::RandChartorCoord(game);
}

std::vector<Mapobject*> Adventure::GetSymbolObjs(std::string symbol)
{
    std::vector<Mapobject*> select;
    for (auto sym: objs) {
        for (auto obj : sym) {
            if(obj && obj->GetSymbol() == symbol)
                select.push_back(obj);
        }
    }

    return select;
}

void Adventure::touched(Mapobject* obj1, Mapobject* obj2)
{
    if(obj1 && obj2) {
        this->handler->handle(obj1, obj2);
    }
}

bool Adventure::IsOutBound(Coord* pos, std::pair<int, int> dpos)
{   
    //TODO: need to fix up dir bound problem
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

void Adventure::refersh(Mapobject* obj, Coord* newPos)
{
    objs[obj->GetCoord()->GetX()][obj->GetCoord()->GetY()] = nullptr;
    obj->SetCoord(newPos);
    objs[newPos->GetX()][newPos->GetY()] = obj;
}

std::pair<int, int> Adventure::GetDirPos(int choose)
{
    auto it = dirmap.find(choose);
    std::string dir = it->second;
    return dirTopos.find(dir)->second;
}

//Gen Monster and treasure and obstacle
Mapobject* Adventure::RandomGenObj(Adventure* game, std::string target)
{   
    Mapobject* obj = Mapobject::GenObj(game, target);
    return obj;
}

Adventure* Adventure::RandChartorCoord(Adventure* game)
{
    Coord* pos = Coord::RandomCoord(game->boundx-1, game->boundy-1);
    if(game->IsNullObj(pos)) {
        game->charactor->SetCoord(pos);
        game->objs[pos->GetX()][pos->GetY()] = game->charactor;
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

void Adventure::SetObj(Mapobject* obj)
{
    objs[obj->GetCoord()->GetX()][obj->GetCoord()->GetY()] = obj;
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
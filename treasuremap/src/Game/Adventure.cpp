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


Adventure::Adventure()
{
    this->handler = new RoleObstacleTouched(new RoleTreasureTouched(nullptr));
    this->objs = std::vector<std::vector<Mapobject*>>(boundx, std::vector<Mapobject*>(boundy, nullptr));
}

Adventure::Adventure(Charator* charator)
{   
    this->handler = new RoleObstacleTouched(new RoleTreasureTouched(nullptr));
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
        //TODO: start round gen obj
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

    return !((haveMonster) || (CharatorHp > 0));
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

    int count = 0;
    while (count < randomNumber) {
        int choice = genchoice(gen);
        
        Mapobject* gens = Adventure::RandomGenObj(game, targets[choice]);
        if(game->IsNullObj(gens->GetCoord())) {
            int x = gens->GetCoord()->GetX();
            int y = gens->GetCoord()->GetY();
            game->objs[x][y] = gens;
            count++;
        }
    }
    
    return Adventure::RandChartorCoord(game);
}

void Adventure::touched(Mapobject* obj1, Mapobject* obj2)
{
    this->handler->handle(obj1, obj2);
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
    std::cout << "in :" << std::endl;
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
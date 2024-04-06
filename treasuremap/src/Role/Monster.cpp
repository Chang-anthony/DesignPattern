#include <Monster.hpp>
#include <Adventure.hpp>
#include <Coord.hpp>
#include <State.hpp>
#include <MonsterAttack.hpp>
#include <Charator.hpp>
#include <cstdlib>
#include <ctime>
#include <set>

Monster::Monster(Coord* pos, Adventure* game) : Role("M", pos, game)
{
    this->SetHp(1);
    SetAttackType(new MonsterAttack(this));
}

void Monster::Do()
{   
    if(pos->distance(game->GetCharator()->GetCoord()) == 1){
        attack();
    }else {
        srand(time(nullptr));
        int randomNumber = rand() % 4;
        std::pair<int, int> dpos = game->GetDirPos(randomNumber);
        while(true){
            if(game->IsOutBound(pos, dpos))
                break;
            else {
                int randomNumber = rand() % 4;
                dpos = game->GetDirPos(randomNumber);
            }
        }
        move(dpos.first, dpos.second);
    }
}

bool Monster::fullHp()
{
    return Hp >= 1;
}

void Monster::gainHp(int Hp)
{
    this->Hp += Hp;
    if(this->Hp > 1)
        this->Hp = 1;
}

Monster* Monster::genMonster(Coord* newPos, Adventure* game)
{
    return new Monster(newPos, game);
}

bool Monster::orderless(int random)
{
    bool flag = true;
    std::set<int> s = std::set<int>();
    std::vector<int> updir = std::vector<int>();
    if(random == 1)
        updir = {1, 3};
    else
        updir = {0, 2};

    srand(time(nullptr));
    int randomNumber = rand() % 2;
    std::pair<int, int> dpos = game->GetDirPos(updir[randomNumber]);
    s.insert(updir[randomNumber]);
    while(flag){
        if(s.size() == 2)
            flag = false;
        if(game->IsOutBound(pos, dpos))
                break;
        else {
            int randomNumber = rand() % 2;
            dpos = game->GetDirPos(updir[randomNumber]);
            s.insert(updir[randomNumber]);
        }
    }
    if(flag) 
        move(dpos.first, dpos.second);

    return flag;
}

Monster::~Monster()
{
}
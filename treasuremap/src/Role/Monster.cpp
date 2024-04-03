#include <Monster.hpp>
#include <Adventure.hpp>
#include <Coord.hpp>
#include <State.hpp>
#include <MonsterAttack.hpp>
#include <Charator.hpp>
#include <cstdlib>
#include <ctime>

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

Monster::~Monster()
{
}
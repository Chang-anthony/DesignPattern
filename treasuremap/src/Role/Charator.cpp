#include <Charator.hpp>
#include <Adventure.hpp>
#include <Coord.hpp>
#include <NormalAttack.hpp>

Charator::Charator(Coord* pos, Adventure* game) : Role("↑", pos, game)
{
    SetHp(300);
    SetAttackType(new NormalAttack(this));
}

void Charator::Do()
{
    std::cout << "請選擇要做的操作: " << std::endl;
    std::cout << "0. 上 \t 1. 右\t 2. 下\t 3. 左\t 4. 攻擊" << std::endl;

    int choice;
    std::cin >> choice;

    if(choice == 4) {
        attack();
    }
    else if(choice >= 0 && choice < 4){
        std::pair<int, int> dpos = game->GetDirPos(choice);
        while (true) {
            if(game->IsOutBound(pos, dpos))
                break;
            else {
                std::cout << "您不能移動超出圖外!!!" << std::endl;
                std::cout << "0. 上 \t 1. 右\t 2. 下\t 3. 左" << std::endl;
                std::cin >> choice;
                dpos = game->GetDirPos(choice);
            }
        }
        SetSymbol(game->GetChooseSymbol(choice));
        move(dpos.first, dpos.second);
    }
    else {
        std::cout << "無效操作, 請在選擇一次!!!" << std::endl;
        Do();
    }
}

bool Charator::fullHp()
{
    return Hp >= 300;
}

void Charator::gainHp(int Hp)
{
    this->Hp += Hp;
    if(this->Hp >= 300)
        this->Hp = 300;
}

Charator::~Charator()
{
}
#include "../include/ShowDownPlayer.hpp"


ShowDownPlayer::ShowDownPlayer():Player()
{
    this->point = 0;
}

void ShowDownPlayer::gainPoint()
{
    this->point += 1;
}

void ShowDownPlayer::NameSelf()
{
    std::cout << "Please Name Your Self :";
    std::string InputName;
    std::cin >> InputName;
    this->SetName(InputName);
}

int ShowDownPlayer::GetPoint()
{
    return this->point;
}

void ShowDownPlayer::SetPoint(int point)
{
    this->point = point;
}


ShowDownPlayer::~ShowDownPlayer()
{

}
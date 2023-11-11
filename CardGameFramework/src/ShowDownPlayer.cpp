#include "../include/ShowDownPlayer.hpp"


ShowDownPlayer::ShowDownPlayer():Player()
{
    this->point = 0;
}

void ShowDownPlayer::gainPoint()
{
    this->point += 1;
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
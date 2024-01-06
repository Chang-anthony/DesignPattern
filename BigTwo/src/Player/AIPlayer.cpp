#include "AIPlayer.hpp"
#include "Card.hpp"
#include <algorithm>
#include <random>



AIPlayer::AIPlayer(/* args */) :Player()
{
}

void AIPlayer::NameSelf()
{
    std::cout << "Please Name yourself :" << std::endl;
    std::string name;
    std::cin >> name;
    this->SetName(name);
}

std::vector<Card*> AIPlayer::Play()
{
    return {};
}

AIPlayer ::~AIPlayer()
{
}
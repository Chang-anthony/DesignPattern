#include "AIPlayer.hpp"
#include "Card.hpp"
#include <algorithm>
#include <random>
#include "utils.h"



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

std::vector<int> AIPlayer::action()
{
    return utils::InputMultipleNums();
}

AIPlayer ::~AIPlayer()
{
}
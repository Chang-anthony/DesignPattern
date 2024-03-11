#include <HumanPlayer.hpp>
#include <Card.hpp>
#include <HandCard.hpp>
#include <utils.h>


HumanPlayer::HumanPlayer():Player()
{
}

void HumanPlayer::NameSelf()
{
    std::cout << "Please Name yourself :" << std::endl;
    std::string name;
    std::cin >> name;
    this->SetName(name);
}

std::vector<int> HumanPlayer::action()
{
    return utils::InputMultipleNums();
}

HumanPlayer::~HumanPlayer()
{
}
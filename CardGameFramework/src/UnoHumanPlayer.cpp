#include "../include/UnoHumanPlayer.hpp"
#include "../include/Card.hpp"
#include "../include/Hand.hpp"
#include "../include/utils/utils.h"

UnoHumanPlayer::UnoHumanPlayer(/* args */)
{
}

Card* UnoHumanPlayer::takeTurn(std::vector<Card*> cards)
{
    std::cout << "玩家 :" << this->GetName() 
        << "可出的手牌為" << std::endl;

    //print出可出手牌
    int count = 1;
    for(auto card:cards)
    {
        std::cout << count << ": ";
        card->render();
        std::cout << " ";
        count++;
    }

    std::cout << std::endl << "玩家 :" << this->GetName() 
        << "請選擇要出什麼牌?" << std::endl; 
    count = utils::HandleInput(1,cards.size());
    std::cout << "玩家 :" << this->GetName() 
        << "選擇第" << count << "張手牌" << std::endl;

    Card* choosecard = cards[count-1];

    return choosecard;
}

UnoHumanPlayer::~UnoHumanPlayer()
{
}
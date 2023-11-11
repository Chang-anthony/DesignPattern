#include "../include/ShowDownHumanPlayer.hpp"
#include "../include/Card.hpp"
#include "../include/Hand.hpp"

ShowDownHumanPlayer::ShowDownHumanPlayer():ShowDownPlayer()
{
}

Card* ShowDownHumanPlayer::takeTurn(std::vector<Card*> cards)
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
    //vector 刪除要用iterator，並且this->GetHandCards()回傳的是handcards位址的拷貝不會真正刪除
    std::vector<Card*>::iterator it = cards.begin() + count -1;
    cards.erase(it);
    this->GetHand()->SetHandCard(cards); 

    return choosecard;
}

ShowDownHumanPlayer::~ShowDownHumanPlayer()
{
}
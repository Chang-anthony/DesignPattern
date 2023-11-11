#include "../include/ShowDownAIPlayer.hpp"
#include "../include/Card.hpp"
#include "../include/Hand.hpp"
#include <algorithm>
#include <random>


ShowDownAIPlayer::ShowDownAIPlayer(/* args */) :ShowDownPlayer()
{
}

Card* ShowDownAIPlayer::takeTurn(std::vector<Card*> cards)
{

    std::srand(unsigned(std::time(nullptr)));
    std::cout << "玩家 :" << this->GetName() 
        << "有的手牌為" << std::endl;

    //print出手牌
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
    
    count = rand() % cards.size(); 
    
    std::cout << "玩家 :" << this->GetName() 
        << "選擇第" << count+1 << "張手牌" << std::endl;

    Card* choosecard = cards[count];
    std::vector<Card*>::iterator it = cards.begin()+count;
    cards.erase(it);
    this->GetHand()->SetHandCard(cards);
    
    return  choosecard;
}

ShowDownAIPlayer ::~ShowDownAIPlayer()
{
}
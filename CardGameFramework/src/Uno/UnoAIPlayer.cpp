#include "../include/Uno/UnoAIPlayer.hpp"
#include "../include/CardFramework/Card.hpp"
#include "../include/CardFramework/Hand.hpp"
#include <iostream>
#include <algorithm>
#include <random>

UnoAIPlayer::UnoAIPlayer(/* args */):UnoPlayer()
{
}

Card* UnoAIPlayer::takeTurn(std::vector<Card*> cards)
{
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
    
    return  choosecard;
}

UnoAIPlayer::~UnoAIPlayer()
{
}
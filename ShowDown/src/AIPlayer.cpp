#include "../include/AIPlayer.hpp"
#include "../include/Card.hpp"
#include "../include/ExchangeCard.hpp"
#include <algorithm>
#include <random>


AIPlayer::AIPlayer(/* args */) :Player(false)
{
}

Card* AIPlayer::ShowCard()
{
    Player* play = this;
    if(this->GetExChangeCard() && this->GetExChangeCard()->GetRound() > 0)
    {
        play = this->GetExChangeCard()->Show(this);
        int round = this->GetExChangeCard()->GetRound();
        this->GetExChangeCard()->SetRound(round-1);
    }


    std::srand(unsigned(std::time(nullptr)));
    std::cout << "玩家 :" << this->GetName() 
        << "有的手牌為" << std::endl;

    //print出手牌
    std::vector<Card*> handcards = play->GetHandCards();
    int count = 1;
    for(auto card:handcards)
    {
        std::cout << count << ": ";
        card->render();
        std::cout << " ";
        count++;
    }
    std::cout << std::endl << "玩家 :" << this->GetName() 
        << "請選擇要出什麼牌?" << std::endl; 
    
    count = rand() % handcards.size(); 
    
    std::cout << "玩家 :" << this->GetName() 
        << "選擇第" << count+1 << "張手牌" << std::endl;

    Card* choosecard = handcards[count];
    std::vector<Card*>::iterator it = handcards.begin()+count;
    handcards.erase(it);
    play->SetHandCards(handcards);
    
    return  choosecard;
}

AIPlayer ::~AIPlayer()
{
}
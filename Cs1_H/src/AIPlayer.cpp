#include "../include/AIPlayer.hpp"
#include "../include/Card.hpp"
#include <algorithm>
#include <random>


AIPlayer::AIPlayer(/* args */) :Player(false)
{
}

Card* AIPlayer::ShowCard()
{
    std::srand(unsigned(std::time(nullptr)));
    std::cout << "玩家 :" << this->GetName() 
        << "有的手牌為" << std::endl;

    //print出手牌
    std::vector<Card*> handcards = this->GetHandCards();
    int count = 1;
    for(auto card:handcards)
    {
        std::cout << count << ": ";
        card->render();
        std::cout << " ";
        count++;
    }
    std::cout << "玩家 :" << this->GetName() 
        << "請選擇要出什麼牌?" << std::endl; 
    
    count = rand() % this->GetHandCards().size(); 
    
    std::cout << "玩家 :" << this->GetName() 
        << "選擇第" << count+1 << "張手牌" << std::endl;

    Card* choosecard = this->GetHandCards()[count];
    //TODO:need to fix erase problem
    std::vector<Card*>::iterator it = handcards.begin()+count;
    handcards.erase(it);
    
    return  choosecard;
}

AIPlayer ::~AIPlayer()
{
}
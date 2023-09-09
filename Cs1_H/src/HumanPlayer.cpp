#include "../include/HumanPlayer.hpp"
#include "../include/Card.hpp"
#include "../include/ExchangeCard.hpp"

HumanPlayer::HumanPlayer():Player(true)
{
}

Card* HumanPlayer::ShowCard()
{
    Player* play = this;
    if(this->GetExChangeCard() && this->GetExChangeCard()->GetRound() > 0)
    {
        play = this->GetExChangeCard()->Show(this);
        int round = this->GetExChangeCard()->GetRound();
        this->GetExChangeCard()->SetRound(round-1);
    }

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
    count = utils::HandleInput(1,handcards.size());
    std::cout << "玩家 :" << this->GetName() 
        << "選擇第" << count << "張手牌" << std::endl;

    Card* choosecard = handcards[count-1];
    //vector 刪除要用iterator，並且this->GetHandCards()回傳的是handcards位址的拷貝不會真正刪除
    std::vector<Card*>::iterator it = handcards.begin() + count -1;
    handcards.erase(it);
    play->SetHandCards(handcards);

    return choosecard;
}

HumanPlayer::~HumanPlayer()
{
}
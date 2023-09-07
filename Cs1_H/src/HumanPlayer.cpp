#include "../include/HumanPlayer.hpp"
#include "../include/Card.hpp"

HumanPlayer::HumanPlayer():Player(true)
{
}

Card* HumanPlayer::ShowCard()
{
    Player* player = this;

    std::cout << "玩家 :" << player->GetName() 
        << "有的手牌為" << std::endl;

    //print出手牌
    std::vector<Card*> handcards = player->GetHandCards();
    int count = 1;
    for(auto card:handcards)
    {
        std::cout << count << ": ";
        card->render();
        std::cout << " ";
        count++;
    }

    std::cout << "玩家 :" << player->GetName() 
        << "請選擇要出什麼牌?" << std::endl; 
    std::cin >> count;
    std::cout << "玩家 :" << player->GetName() 
        << "選擇第" << count << "張手牌" << std::endl;

    Card* choosecard = handcards[count-1];
    //vector 刪除要用iterator，並且this->GetHandCards()回傳的是handcards位址的拷貝不會真正刪除
    std::vector<Card*>::iterator it = handcards.begin() + count -1;
    handcards.erase(it);
    player->SetHandCards(handcards);

    return choosecard;
}

HumanPlayer::~HumanPlayer()
{
}
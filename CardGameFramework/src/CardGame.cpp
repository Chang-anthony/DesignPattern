#include "../include/CardGame.hpp"
#include "../include/Deck.hpp"
#include "../include/Player.hpp"
#include "../include/utils/utils.h"
#include "../include/Card.hpp"

CardGame::CardGame(std::vector<Player*> player,Deck* deck)
{
    utils::SizeShouldBe(player,4);
    this->players = player;
    this->deck = deck;
}


void CardGame::GameStart()
{
    std::cout << "Game Start " << std::endl;
    std::cout << "請玩家為自己取名" << std::endl;
    for(auto player:this->players)
        player->NameSelf();

    std::cout << "牌堆洗牌" << std::endl;
    this->deck->Suffle();
    std::cout << "洗牌結束" << std::endl;

    std::cout << "開始抽牌" << std::endl;
    while(this->DrawCardEnd())
    {
        for(auto player:this->players)
        {
            Card* card = this->deck->DrawCard();
            player->AddCard(card);
        }
    }

    while (this->IsGameEnd())
    {
        this->Round();
    }

    Player* winner = this->GetWinner();
    this->GameEnd(winner);  
}

void CardGame::GameEnd(Player* winner)
{
    std::cout << "遊戲結束!!! 贏家為 :" << winner->GetName() << std::endl;
}


std::vector<Player*> CardGame::GetPlayers()
{
    return this->players;
}

Deck* CardGame::GetDeck()
{
    return this->deck;
}

void CardGame::SetPlayers(std::vector<Player*> players)
{
    utils::SizeShouldBe(players,4);
    this->players = players;
}

void CardGame::SetDeck(Deck* deck)
{
    utils::RequireNonNull(deck);
    this->deck = deck;
}

CardGame::~CardGame()
{
}
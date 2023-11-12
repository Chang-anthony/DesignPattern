#include "../include/ShowDown/Showdown.hpp"
#include "../include/CardFramework/Deck.hpp"
#include "../include/CardFramework/Player.hpp"
#include "../include/CardFramework/Card.hpp"
#include "../include/ShowDown/ShowDownPlayer.hpp"
#include "../include/ShowDown/ShowDownCard.hpp"
#include "../include/CardFramework/Hand.hpp"
#include <algorithm>
#include <typeinfo>
#include <random>


Showdown::Showdown(std::vector<Player*> players,Deck* deck):CardGame(players,deck)
{
    this->drawcardend = 0;
    this->round = 0;
}

bool Showdown::DrawCardEnd()
{
    this->drawcardend++;
    return this->drawcardend <= 13; 
}

bool  Showdown::IsGameEnd()
{
    return this->round < 13;
}

Player* Showdown::GetWinner()
{
    Player* win = nullptr;
    int maxv = 0;
    for(auto player:this->GetPlayers())
    {
        ShowDownPlayer* p = dynamic_cast<ShowDownPlayer*>(player);
        if(p->GetPoint() > maxv)
        {
            win = p;
            maxv = p->GetPoint();
        }
    }

    return win;
}


void Showdown::Round()
{
    std::vector<Card*> show = std::vector<Card*>();
    
    for(auto player:this->GetPlayers())
    {
        show.push_back(player->takeTurn(player->GetHand()->GetHandCard()));
    }

    this->Render(show);
    ShowDownPlayer* winner = dynamic_cast<ShowDownPlayer*>(this->Bigger(show));
    std::cout << "這回合的勝者為 :" << winner->GetName() << std::endl;
    winner->gainPoint();
    this->round++;
}

Player* Showdown::Bigger(std::vector<Card*> cards)
{
    std::vector<Player*> players = this->GetPlayers();
    Player* winner = players[0];

    ShowDownCard* bigger = dynamic_cast<ShowDownCard*>(cards[0]);

    for(int i = 1 ; i < 4 ; i++)
    {
        ShowDownCard* next = dynamic_cast<ShowDownCard*>(cards[i]);
        if(!bigger->IsBigger(next))
        {
            bigger = next;
            winner = players[i];
        }
    }
    return winner;
}

void Showdown::Render(std::vector<Card*> cards)
{
    int count = 1;
    for(auto card:cards)
    {
        std::cout << "P" << count << ": ";
        card->render();
        std::cout << " ";
        count++;
    }
    std::cout << std::endl;
}

Showdown::~Showdown()
{
}
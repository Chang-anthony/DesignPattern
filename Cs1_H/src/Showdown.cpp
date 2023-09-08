#include "../include/Showdown.hpp"
#include "../include/Deck.hpp"
#include "../include/Player.hpp"
#include "../include/Card.hpp"
#include <algorithm>
#include <random>

Showdown::Showdown(Deck* deck,std::vector<Player*> players):deck(deck),players(players)
{
    utils::SizeShouldBe(players,4);
}

void Showdown::GameStart()
{
    std::cout << "ShowDown遊戲開始!!!" << std::endl;
    std::cout << "請各位玩家取名!!!" << std::endl;
}

Deck* Showdown::GetDeck()
{
    return this->deck;
}

std::vector<Player*> Showdown::GetPlayers()
{
    return  this->players;
}

void Showdown::SetDeck(Deck* deck)
{
    this->deck = deck;
}

void Showdown::NameHimSelf()
{
    for(auto player:this->players)
        player->NameSelf();
}

void Showdown::DoShuffle()
{
    std::cout << "開始洗牌!!!" << std::endl;
    this->GetDeck()->Suffle();
    std::cout << "洗牌結束!!!" << std::endl;
}

void Showdown::DrawCard()
{
    std::cout << "各玩家輪流抽牌" << std::endl;
    for(int i = 0 ; i < 13 ; i++ )
    {
        for(auto player:this->players)
            player->DrawCard(this->deck);  
    }
}

//TODO: need to do Round Function
void Showdown::Round()
{
    std::vector<Card*> show = std::vector<Card*>();
    for(auto player:players)
    {
        if(player->GetExchange())
        {
            
            std::cout << "請選擇 " << "1.行使交換權" << " " << "2. Show一張卡牌"  << std::endl;
            if(player->GetIsHuman())
            {
                int choose = 0;
                std::cin >> choose;
                if(choose == 1)
                {
                    std::vector<Player*> can_choose = this->GetPlayers();
                    can_choose.erase(std::remove_if(can_choose.begin(),can_choose.end(),[player](Player* remove)
                    {
                        return remove == player;
                    }),can_choose.end());
                    std::cout << "請輸入 1 ~ 3的數字選擇想交換卡牌的玩家" << std::endl;
                    std::cin >> choose;
                    player->DoExchange(can_choose[choose-1]);
                }
                else
                {
                    if(player->GetExChangeCard())
                    {
                        
                        
                    }
                    else
                    {
                        show.push_back(player->ShowCard());
                    }
                }
            }
            else
            {
                
            }
        }
        else
        {

        }
    }
}

void Showdown::Render(std::vector<Card*> cards)
{
    int count = 1;
    for(auto card:cards)
    {
        std::cout << "P" << count << ": " ;
        card->render();
    }
}

Player* Showdown::Bigger(std::vector<Card*> cards)
{
    std::vector<Player*> players = this->GetPlayers();
    Player* winner = players[0];
    Card* bigger = cards[0];
    for(int i = 1 ; i < 4 ; i++)
    {
        if(!bigger->IsBigger(cards[i]))
        {
            bigger = cards[i];
            winner = players[i];
        }
    }
    return winner;
}

void Showdown::GameEnd()
{
    int point = 0;
    Player* winner = nullptr;
    for(auto player:this->players)
    {
        if(point < player->GetPoint())
        {
            winner = player;
            point = std::max(point,player->GetPoint());
        }
    }

    std::cout << "遊戲結束!!!" << "  勝利的玩家為 :"
        << winner->GetName() <<  std::endl;
}

void Showdown::SetPlayers(std::vector<Player*> players)
{
    this->players = players;
}

Showdown::~Showdown()
{
}
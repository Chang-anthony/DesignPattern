#include "../include/Showdown.hpp"
#include "../include/Deck.hpp"
#include "../include/Player.hpp"
#include "../include/Card.hpp"
#include "../include/ExchangeCard.hpp"
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


void Showdown::Round()
{
    std::vector<Card*> show = std::vector<Card*>();
    for(auto player:players)
    {
        if(player->GetIsHuman())
        {
            if(player->GetExchange())
            {
                std::cout << "請選擇 " << "1.行使交換權" << " " << "2. Show一張卡牌"  << std::endl;
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
                    choose = utils::HandleInput(1,3);
                    std::cout << "玩家:" << player->GetName() << " 選擇 :" << can_choose[choose-1]->GetName() << " 交換手牌" << std::endl;
                    player->DoExchange(can_choose[choose-1]);
                }
            }
            else
            {
                std::cout << "您已沒有交換卡牌的權利 直接選擇出牌" << std::endl; 
            }
        }
        else
        {
            if(player->GetExchange())
            {
                std::cout << "請選擇 " << "1.行使交換權" << " " << "2. Show一張卡牌"  << std::endl;
                // std::srand(unsigned(std::time(nullptr)));
                int choose = rand() % 2;
                if(choose == 1)
                {
                    std::vector<Player*> can_choose = this->GetPlayers();
                    can_choose.erase(std::remove_if(can_choose.begin(),can_choose.end(),[player](Player* remove)
                    {
                        return remove == player;
                    }),can_choose.end());
                    std::cout << "請輸入 1 ~ 3的數字選擇想交換卡牌的玩家" << std::endl;
                    choose = rand() % 3;
                    std::cout << "玩家:" << player->GetName() << " 選擇 :" << can_choose[choose]->GetName() << " 交換手牌" << std::endl;
                    player->DoExchange(can_choose[choose]);
                }
            }
            else
            {
                std::cout << "您已沒有交換卡牌的權利 直接選擇出牌" << std::endl; 
            }
        }
    }

    for(auto player:this->players)
    {
        show.push_back(this->DoShowCard(player));
    }

    this->Render(show);
    Player* winner = this->Bigger(show);
    std::cout << "這回合的勝者為 :" << winner->GetName() << std::endl;
    winner->SetPoint(winner->GetPoint()+1);
}

Card* Showdown::DoShowCard(Player* player)
{
    return player->ShowCard(); 
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
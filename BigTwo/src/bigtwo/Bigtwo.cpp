#include <Bigtwo.hpp>
#include <Player.hpp>
#include <Card.hpp>
#include <CardPatternHandler.hpp>
#include <Round.hpp>
#include <HandCard.hpp>
#include <Deck.hpp>
#include <BigTwo_paser.hpp>
#include <FileIterator.hpp>
#include <utility>
#include <iostream>


//TODO 1: need to test comparehandler and vaild handler
//TODO 2: need to test first player and first Round
//TODO 3: need to test newRound and Round cpp file takeTurn function

Bigtwo::Bigtwo(Deck* deck,std::vector<Player*> players, CardPatternHandler* handler)
{
    this->SetDeck(deck);
    this->SetPlayers(players);
    this->SetPatternHandler(handler);
}

void Bigtwo::GameStart()
{
    this->deck->Suffle();
    for(auto card:this->deck->GetCards()){
        card->render();
        std::cout << " ";
    }
    std::cout << std::endl;

    for(auto player:this->players)
        player->NameSelf();
    
    std::cout << "抽牌" << std::endl;
    this->doDeal();
    
    //first round
    Player* topplayer = this->FristPlayer();
    Round* first = this->FirstRound(topplayer);
    topplayer = first->takeTurn(this->players);

    while (!this->isEnd())
    {
        Round* newRound = this->newRound(topplayer);
        topplayer = newRound->takeTurn(this->players);
    }
    
    this->GameEnd();
}

Player* Bigtwo::FristPlayer()
{
    Player* firstplay = nullptr;
    for(auto player: players){
        for(auto card: player->GetHandCard()->GetCards()){
            std::string rank = RankToName(card->GetRank());
            std::string suit = SuitToName(card->GetSuit());
            if(rank == "3" && suit == "Club"){
                firstplay = player;
                break;
            }
        }
    }

    return firstplay;
}

bool Bigtwo::vaildHandle(std::vector<Card*> cards)
{
    if(this->handler->vaild(cards))
        return true;
    else
        return false;
}

bool Bigtwo::CampareHandle(std::vector<Card*> cards,std::vector<Card*> topplay)
{
    bool vaild = this->handler->vaild(cards);
    bool IsSame = this->handler->isSamePatternHandle(cards,topplay);

    if(IsSame && vaild){
        return this->handler->BiggerHandle(cards,topplay);
    }
    else{
        return IsSame && vaild;
    }
}

std::string Bigtwo::PatternNameHandle(std::vector<Card*> cards)
{
    return this->handler->PatternNameHandle(cards);
}

Round* Bigtwo::FirstRound(Player* topplayer)
{
    std::cout << "新的回合開始了。" << std::endl;
    std::cout << "輪到" << topplayer->GetName() <<  "了" << std::endl;

    bool vaild = false;
    std::vector<Card*> topplay = std::vector<Card*>();

    while(!vaild){
        std::vector<Card*> cards = topplayer->Play();

        if(cards.size() == 0)
        {
            std::cout << "你不能在新的回合中喊 PASS" << std::endl;
        }

        if(this->handler->vaild(cards))
        {
            bool check = false;
            for(auto card:cards){
                int rank = RankToNumber(card->GetRank());
                int suit = SuitToNumber(card->GetSuit());
                if(rank == 3 && suit == 1)
                    check = true;
            }

            if(check){
                vaild = true;
                topplay = cards;
                this->Render(topplayer, topplay);
            }
            else{
                std::cout << "此牌型不合法，請再嘗試一次。" << std::endl;
            }
        }
        else{
            std::cout << "此牌型不合法，請再嘗試一次。" << std::endl;
        }
    }

    Round* newRound = new Round(topplayer, topplay, this);
    this->rounds.push_back(newRound);

    return newRound;
}

Round* Bigtwo::newRound(Player* topplayer)
{
    std::cout << "新的回合開始了。" << std::endl;
    std::cout << "輪到" << topplayer->GetName() <<  "了" << std::endl;

    bool vaild = false;
    std::vector<Card*> topplay = std::vector<Card*>();

    while(!vaild){
        std::vector<Card*> cards = topplayer->Play();

        if(cards.size() == 0){
            std::cout << "你不能在新的回合中喊 PASS" << std::endl;
        }

        if(this->handler->vaild(cards)){
            vaild = true;
            topplay = cards;
            this->Render(topplayer, topplay);
        }
        else{
            std::cout << "此牌型不合法，請再嘗試一次。" << std::endl;
        }
    }

    Round* newRound = new Round(topplayer,topplay,this);
    this->rounds.push_back(newRound);

    return newRound;
}

void Bigtwo::Render(Player* play, std::vector<Card*> cards)
{
    std::cout << "玩家 " << play->GetName() << " 打出了 " 
    << this->PatternNameHandle(cards) << " ";
    for(auto card:cards)
        card->render();
}

bool Bigtwo::isEnd()
{
    bool end = false;
    for(auto player:this->players)
    {
        if(player->isHandCardEmpty())
        {
            end = true;
            break;
        }
    }

    return end;
}

void Bigtwo::doDeal()
{
    while (this->deck->GetCards().size() > 0)
    {
        for (auto player:this->players)
        {
            player->Deal(this->deck);
        }
    }

    for (auto play : this->players)
    {
        play->SortHandCard();
    }
    
}

void Bigtwo::GameEnd()
{
    Player* winner = nullptr;
    for(auto player:this->players)
    {
        if(player->isHandCardEmpty())
        {
            winner = player;
            break;
        }
    }
    std::cout<< "遊戲結束，遊戲的勝利者為 " << winner->GetName() << "" << std::endl;
}

std::vector<Player*> Bigtwo::GetPlayers()
{
    return this->players;
}

Deck* Bigtwo::GetDeck()
{
    return this->deck;
}

void Bigtwo::AddRound(Round* round)
{
    utils::RequireNonNull(round);
    this->rounds.push_back(round);
}

void Bigtwo::SetPlayers(std::vector<Player*> players)
{
    utils::SizeShouldBe(players,4);
    this->players = players;
}

void Bigtwo::SetDeck(Deck* deck)
{
    utils::RequireNonNull(deck);
    this->deck = deck;
}

void Bigtwo::SetPatternHandler(CardPatternHandler* handler)
{
    utils::RequireNonNull(handler);
    this->handler = handler;   
}

void Bigtwo::RunTest(Bigtwo* game, std::vector<std::vector<int>> plays)
{
    std::cout << "抽牌" << std::endl;
    game->doDeal();

    Player* topplayer = game->FristPlayer();

    std::pair P = game->FirstRound(topplayer, plays);
    Round* first = P.first;

    std::pair result = first->takeTurn(game->GetPlayers(), P.second);
    topplayer = result.first;
    plays = result.second;

    while (!game->isEnd())
    {
        auto map = game->newRound(topplayer, plays);
        Round* newRound = map.first;

        auto result = newRound->takeTurn(game->GetPlayers(), map.second);
        topplayer = result.first;
        plays = result.second;
    }
    
    game->GameEnd();
}


//TODO: can use templatemethod
std::pair<Round*, std::vector<std::vector<int>>> Bigtwo::FirstRound(Player* topplayer, std::vector<std::vector<int>> plays)
{
    std::cout << "新的回合開始了。" << std::endl;
    std::cout << "輪到" << topplayer->GetName() <<  "了" << std::endl;

    bool vaild = false;
    std::vector<Card*> topplay = std::vector<Card*>();

    while(!vaild && plays.size() > 0){
        std::vector<Card*> cards = topplayer->Play(plays[0]);
        plays.erase(plays.begin());

        if(cards.size() == 0)
        {
            std::cout << "你不能在新的回合中喊 PASS" << std::endl;
        }

        if(this->handler->vaild(cards))
        {
            bool check = false;
            for(auto card:cards){
                int rank = RankToNumber(card->GetRank());
                int suit = SuitToNumber(card->GetSuit());
                if(rank == 3 && suit == 1)
                    check = true;
            }

            if(check){
                vaild = true;
                topplay = cards;
                this->Render(topplayer, topplay);
            }
            else{
                std::cout << "此牌型不合法，請再嘗試一次。" << std::endl;
            }
        }
        else{
            std::cout << "此牌型不合法，請再嘗試一次。" << std::endl;
        }
    }

    Round* newRound = new Round(topplayer, topplay, this);
    this->rounds.push_back(newRound);

    return std::make_pair(newRound, plays);
}

std::pair<Round*, std::vector<std::vector<int>>> Bigtwo::newRound(Player* topplayer, std::vector<std::vector<int>> plays)
{
    std::cout << "新的回合開始了。" << std::endl;
    std::cout << "輪到" << topplayer->GetName() <<  "了" << std::endl;

    bool vaild = false;
    std::vector<Card*> topplay = std::vector<Card*>();

    while(!vaild && plays.size() > 0){
        std::vector<Card*> cards = topplayer->Play(plays[0]);
        plays.erase(plays.begin());

        if(cards.size() == 0){
            std::cout << "你不能在新的回合中喊 PASS" << std::endl;
        }

        if(this->handler->vaild(cards)){
            vaild = true;
            topplay = cards;
            this->Render(topplayer, topplay);
        }
        else{
            std::cout << "此牌型不合法，請再嘗試一次。" << std::endl;
        }
    }

    Round* newRound = new Round(topplayer,topplay,this);
    this->rounds.push_back(newRound);

    return std::make_pair(newRound, plays);
}

Bigtwo::~Bigtwo()
{
}
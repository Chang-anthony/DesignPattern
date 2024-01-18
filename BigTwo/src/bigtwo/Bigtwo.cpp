#include <Bigtwo.hpp>
#include <Player.hpp>
#include <Card.hpp>
#include <CardPatternHandler.hpp>
#include <Round.hpp>
#include <HandCard.hpp>
#include <Deck.hpp>

Bigtwo::Bigtwo(Deck* deck,std::vector<Player*> players,CardPatternHandler* handler)
{
    this->SetDeck(deck);
    this->SetPlayers(players);
    this->SetPatternHandler(handler);
}

void Bigtwo::GameStart()
{

}

Round* Bigtwo::FristPlay()
{
    return nullptr;
}

bool Bigtwo::vaildHandle(std::vector<Card*> cards)
{
    return this->handler->vaild(cards);
}

bool Bigtwo::CampareHandle(std::vector<Card*> cards,std::vector<Card*> topplay)
{
    bool IsSame = this->handler->isSamePatternHandle(cards,topplay);
    if(IsSame)
    {
        return this->handler->BiggerHandle(cards,topplay);
    }
    else
    {
        std::cout << "此牌型不合法，請再嘗試一次。" << std::endl;
        return IsSame;
    }
}

Round* Bigtwo::newRound(Player* topplayer)
{
    std::vector<Card*> topplay = topplayer->Play();
    //TODO:pattern handler
    Round* newround = new Round(topplayer,topplay,this);
    this->rounds.push_back(newround);

    return newround;
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
    std::cout<< "遊戲結束，遊戲的勝利者為 <" << winner->GetName() << ">" << std::endl;
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

Bigtwo::~Bigtwo()
{
}
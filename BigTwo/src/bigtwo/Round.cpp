#include <Round.hpp>
#include <Bigtwo.hpp>
#include <Card.hpp>
#include <Player.hpp>


Round::Round(Player* TopPlayer,std::vector<Card*> TopPlay,Bigtwo* game)
{
    this->SetTopPlayer(TopPlayer);
    this->SetTopPlay(TopPlay);
    this->SetBigtwo(game);
}

//TODO: round takeTurn funtion
Player* Round::takeTurn(std::vector<Player*> players)
{
    return this->TopPlayer;
}

Player* Round::GetTopPlayer()
{
    return this->TopPlayer;
}

std::vector<Card*> Round::GetTopPlay()
{
    return this->TopPlay;
}

Bigtwo* Round::GetBigTwo()
{
    return this->game;
}

void Round::SetBigtwo(Bigtwo* game)
{
    utils::RequireNonNull(game);
    this->game = game;
}

void Round::SetTopPlay(std::vector<Card*> topplay)
{
    utils::SizeShouldBigger(topplay,0);
    this->TopPlay = topplay;
}

void Round::SetTopPlayer(Player* topplayer)
{
    utils::RequireNonNull(topplayer);
    this->TopPlayer = topplayer;
}

Round::~Round()
{
}
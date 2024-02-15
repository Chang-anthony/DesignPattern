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

Player* Round::takeTurn(std::vector<Player*> players)
{
    int count = 0;
    for(auto player:players){
        if(player == this->TopPlayer)
            break;
        count++;
    }

    while (!this->game->isEnd()){
        Player* taketurn = players[count];
        std::cout << "輪到<" << taketurn->GetName() <<  ">了" << std::endl;
        //Play card take turn
        std::vector<Card*> play = taketurn->Play();

        if(play.size() == 0){
            std::cout << "玩家 < " << taketurn->GetName() << "> PASS" << std::endl;
            count = (count + 1) % 4;
        }
        else{
            if(this->game->CampareHandle(play,this->TopPlay)){
                // remove played card
                taketurn->RemoveCardFromHand(play);
                this->game->Render(taketurn, play);
                this->TopPlay = play;
                this->TopPlayer = taketurn;
                count = (count + 1) % 4;
            }
            else{
                std::cout << "此牌型不合法，請再嘗試一次。" << std::endl;
            }
        }
    }
    
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
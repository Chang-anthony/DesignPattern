#include <HumanPlayer.hpp>
#include <Card.hpp>
#include <HandCard.hpp>
#include <utils.h>


HumanPlayer::HumanPlayer():Player()
{
}

void HumanPlayer::NameSelf()
{
    std::cout << "Please Name yourself :" << std::endl;
    std::string name;
    std::cin >> name;
    this->SetName(name);
}

//TODO: need to test can move to player class be a hook
std::vector<Card*> HumanPlayer::Play()
{
    this->RenderHandCard();
    std::vector<int> want_play = utils::InputMultipleNums();

    if(want_play.size() == 1 && want_play[0] == -1)
        return {};
    else{
        if(this->verfiyInput(want_play)){
            std::vector<Card*> plays = std::vector<Card*>();
            for(auto input: want_play){
                plays.push_back(this->GetHandCard()->GetCards()[input]);
            }
            return plays;
        }
        else{
            return this->Play();
        }
    }
}

std::vector<Card*> HumanPlayer::Play(std::vector<int> play)
{
    this->RenderHandCard();

    if(play.size() == 1 && play[0] == -1)
        return {};
    else{
        if(this->verfiyInput(play)){
            std::vector<Card*> plays = std::vector<Card*>();
            for(auto input: play){
                plays.push_back(this->GetHandCard()->GetCards()[input]);
            }
            return plays;
        }
        else{
            return {};
        }
    }
}

HumanPlayer::~HumanPlayer()
{
}
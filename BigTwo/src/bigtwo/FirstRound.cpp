#include <FirstRound.hpp>
#include <Bigtwo.hpp>
#include <Card.hpp>
#include <Player.hpp>

FirstRound::FirstRound(Player* TopPlayer, std::vector<Card*> TopPlay, Bigtwo* game):Round(TopPlayer, TopPlay, game)
{
}

FirstRound* FirstRound::newRound(Player* topplayer, Bigtwo *game)
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

        if(game->vaildHandle(cards) && FirstRound::condition(cards))
        {
            vaild = true;
            topplay = cards;
            game->Render(topplayer, topplay);
        }
        else{
            std::cout << "此牌型不合法，請再嘗試一次。" << std::endl;
        }
    }

    FirstRound* newRound = new FirstRound(topplayer, topplay, game);

    return newRound;
}

std::pair<FirstRound*, std::vector<std::vector<int>>> FirstRound::newRound
        (Player* topplayer, Bigtwo *game, std::vector<std::vector<int>> plays)
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

        if(game->vaildHandle(cards) && FirstRound::condition(cards))
        {
            vaild = true;
            topplay = cards;
            game->Render(topplayer, topplay);
        }
        else{
            std::cout << "此牌型不合法，請再嘗試一次。" << std::endl;
        }
    }

    FirstRound* newRound = new FirstRound(topplayer, topplay, game);

    return std::make_pair(newRound, plays);
}

bool FirstRound::condition(std::vector<Card*> cards)
{
    bool check = false;
    for(auto card:cards){
        std::string rank = RankToName(card->GetRank());
        std::string suit = SuitToName(card->GetSuit());
        if(rank == "3" && suit == "Club")
            check = true;
    }

    return check;
}

FirstRound::~FirstRound()
{
}
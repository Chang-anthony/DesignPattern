#include <PairHandler.hpp>
#include <Card.hpp>


PairHandler::PairHandler(CardPatternHandler* next):CardPatternHandler(next)
{
}

//TODO:Have problem
bool PairHandler::isBigger(std::vector<Card*> pattern1,std::vector<Card*> pattern2)
{
    return false;
}

bool PairHandler::match(std::vector<Card*> cards)
{
    if(cards.size() == 2)
    {
        int count = 0;
        int number = RankToNumber(cards[0]->GetRank());
        for(auto card:cards)
        {
            if(RankToNumber(card->GetRank()) == number)
                count++;
        }
        if(count == 2)
            return true;
        else
            return false;
    }
    return false;
}

std::string PairHandler::GetPatternName()
{
    return "Pair";
}

std::string PairHandler()
{
    return "Pair";
}

PairHandler::~PairHandler()
{
}
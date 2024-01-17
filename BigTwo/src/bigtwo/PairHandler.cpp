#include <PairHandler.hpp>
#include <Card.hpp>


PairHandler::PairHandler(CardPatternHandler* next):CardPatternHandler(next)
{
}

bool PairHandler::isBigger(std::vector<Card*> pattern1,std::vector<Card*> pattern2)
{
    Card* card1 = pattern1[0]->isBigger(pattern1[1]) ? pattern1[0] : pattern1[1];
    Card* card2 = pattern2[0]->isBigger(pattern2[1]) ? pattern2[0] : pattern2[1];

    return card1->isBigger(card2);
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
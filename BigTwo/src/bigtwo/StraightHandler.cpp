#include <StraightHandler.hpp>
#include <Card.hpp>

StraightHandler::StraightHandler(CardPatternHandler* next):CardPatternHandler(next)
{
}

bool StraightHandler::isBigger(std::vector<Card*> pattern1,std::vector<Card*> pattern2)
{
    Card* card1 = this->GetMaxCard(pattern1);
    Card* card2 = this->GetMaxCard(pattern2);

    return card1->isBigger(card2);
}

Card* StraightHandler::GetMaxCard(std::vector<Card*> cards)
{
    Card* max_card = cards[0];
    for(int i = 1; i < cards.size() ; i++)
    {
        if(!max_card->isBigger(cards[i]))
            max_card = cards[i];
    }
    
    return max_card;
}

bool StraightHandler::match(std::vector<Card*> cards)
{
    if(cards.size() == 5)
    {
        int first = RankToNumber(cards[0]->GetRank());
        for(int i = 1; i < cards.size() ; i++)
        {
            if(RankToNumber(cards[i]->GetRank()) == first+1)
                first++;
            else
                break;
        }
        return true;
    }

    return false;
}

std::string StraightHandler::GetPatternName()
{
    return "Straight";
}

StraightHandler::~StraightHandler()
{
}
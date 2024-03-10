#include <FullHouseHandler.hpp>
#include <Card.hpp>
#include <map>

FullHouseHandler::FullHouseHandler(CardPatternHandler* next):CardPatternHandler(next)
{
}

bool FullHouseHandler::isBigger(std::vector<Card*> pattern1,std::vector<Card*> pattern2)
{
    Card* card1 = this->GetThreeMaxCard(pattern1);
    Card* card2 = this->GetThreeMaxCard(pattern2);

    return card1->isBigger(card2);
}

Card* FullHouseHandler::GetThreeMaxCard(std::vector<Card*> cards)
{
    std::map<int,std::vector<Card*>> m = std::map<int,std::vector<Card*>>();
    for(auto card: cards)
        m[RankToNumber(card->GetRank())];
    
    std::vector<Card*> candidate = std::vector<Card*>();
    for(auto v:m)
    {
        if(v.second.size() == 3)
        {
            candidate = v.second;
            break;
        }
    }

    Card* max_card = candidate[0];
    for(int i = 1 ; i < candidate.size(); i++)
    {
        if(!max_card->isBigger(candidate[i]))
            max_card = candidate[i];
    }
    return max_card;
}

bool FullHouseHandler::match(std::vector<Card*> cards)
{
    if(cards.size() == 5)
    {
        std::map<Rank,int> m = std::map<Rank,int>();

        for(auto card:cards)
            m[card->GetRank()]++;
        
        bool three = false;
        bool two = false;
        for(auto v:m)
        {
            if(v.second == 3)
                three = true;
            if(v.second == 2)
                two = true;
        }

        return three && two;
    }

    return false;
}

std::string FullHouseHandler::GetPatternName()
{
    return "FullHouse";
}

FullHouseHandler::~FullHouseHandler()
{
}
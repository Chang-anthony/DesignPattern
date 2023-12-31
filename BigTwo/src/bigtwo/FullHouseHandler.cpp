#include <FullHouseHandler.hpp>
#include <Card.hpp>
#include <map>

FullHouseHandler::FullHouseHandler(CardPatternHandler* next):CardPatternHandler(next)
{
}

bool FullHouseHandler::isBigger(std::vector<Card*> pattern1,std::vector<Card*> pattern2)
{
    return false;
}

bool FullHouseHandler::match(std::vector<Card*> cards)
{
    if(cards.size() == 5)
    {
        std::map<Rank,int> m = std::map<Rank,int>();

        for(auto card:cards)
            m[card->GetRank()]++;
        
        bool three = false;
        bool two = true;
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
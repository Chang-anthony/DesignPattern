#include <SingleHandler.hpp>

SingleHandler::SingleHandler(CardPatternHandler* next):CardPatternHandler(next)
{
}

bool SingleHandler::isBigger(std::vector<Card*> pattern1,std::vector<Card*> pattern2)
{
    return false;
}

bool SingleHandler::match(std::vector<Card*> cards)
{
    return cards.size() == 1;
}

std::string SingleHandler::GetPatternName()
{
    return "Single";
}

SingleHandler::~SingleHandler()
{
}
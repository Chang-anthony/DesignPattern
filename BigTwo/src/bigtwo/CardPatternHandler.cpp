#include <Card.hpp>
#include <CardPatternHandler.hpp>


CardPatternHandler::CardPatternHandler(CardPatternHandler* next):next(next)
{
}

bool CardPatternHandler::isSamePatternHandle(std::vector<Card*> pattern1,std::vector<Card*> pattern2)
{
    std::string type1 = this->vaildPatternHandle(pattern1);
    std::string type2 = this->vaildPatternHandle(pattern2);
    bool vaild = (type1 != "") && (type2 != "") && (type1 == type2); 
    return vaild;
}

bool CardPatternHandler::BiggerHandle(std::vector<Card*> pattern1,std::vector<Card*> pattern2)
{
    bool IsSame = this->isSamePatternHandle(pattern1,pattern2);
    if(IsSame)
    {
        return this->isBigger(pattern1,pattern2);
    }
    else
        return IsSame;
}

std::string CardPatternHandler::vaildPatternHandle(std::vector<Card*> cards)
{
    if(this->match(cards))
    {
        return this->next->GetPatternName(cards);
    }
    else
    {
        return this->next->vaildPatternHandle(cards);
    }
}

CardPatternHandler::~CardPatternHandler()
{
}
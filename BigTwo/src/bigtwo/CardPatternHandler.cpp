#include <Card.hpp>
#include <CardPatternHandler.hpp>
#include <map>

std::map<std::string,std::string> patternToname = 
{
    {"Single","單張"},
    {"Pair","對子"},
    {"Straight","順子"},
    {"FullHouse","葫蘆"},
    {"Quads","鐵支"}
};



CardPatternHandler::CardPatternHandler(CardPatternHandler* next):next(next)
{
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

bool CardPatternHandler::isSamePatternHandle(std::vector<Card*> pattern1,std::vector<Card*> pattern2)
{
    std::string type1 = this->PatternNameHandle(pattern1);
    std::string type2 = this->PatternNameHandle(pattern2);
    bool vaild = (type1 != "") && (type2 != "") && (type1 == type2); 
    return vaild;
}

std::string CardPatternHandler::PatternNameHandle(std::vector<Card*> cards)
{
    if(this->match(cards))
    {
        return patternToname[this->GetPatternName()];
    }
    else
    {   
        //check next handler no null
        if(this->next)
            return this->next->PatternNameHandle(cards);
        else
            return "";
    }
}

CardPatternHandler::~CardPatternHandler()
{
}
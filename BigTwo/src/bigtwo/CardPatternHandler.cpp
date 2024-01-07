#include <Card.hpp>
#include <CardPatternHandler.hpp>


CardPatternHandler::CardPatternHandler(CardPatternHandler* next):next(next)
{
}

bool CardPatternHandler::vaild(std::vector<Card*> pattern1,std::vector<Card*> pattern2)
{
    std::string type1 = this->matchtype(pattern1);
    std::string type2 = this->matchtype(pattern2);
    bool vaild = (type1 != "") && (type2 != "") && (type1 == type2); 
    
    return vaild;
}

CardPatternHandler::~CardPatternHandler()
{
}
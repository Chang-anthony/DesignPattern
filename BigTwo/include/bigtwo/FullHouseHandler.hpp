#ifndef _FULLHOUSEHANDLER_H_
#define _FULLHOUSEHANDLER_H_

#include <CardPatternHandler.hpp>
class Card;

class FullHouseHandler : public CardPatternHandler
{
private:
    /* data */
    bool isBigger(std::vector<Card*> pattern1,std::vector<Card*> pattern2) override;
    bool match(std::vector<Card*> cards) override;
    std::string GetPatternName() override;

public:
    FullHouseHandler(CardPatternHandler* next);
    ~FullHouseHandler();
    
protected:
    Card* GetThreeMaxCard(std::vector<Card*> cards);
};

#endif /* _FULLHOUSEHANDLER_H_ */

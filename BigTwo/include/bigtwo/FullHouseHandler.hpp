#ifndef _FULLHOUSEHANDLER_H_
#define _FULLHOUSEHANDLER_H_

#include <CardPatternHandler.hpp>
class Card;

class FullHouseHandler : public CardPatternHandler
{
private:
    /* data */
public:
    FullHouseHandler(CardPatternHandler* next);
    ~FullHouseHandler();

    bool isBigger(std::vector<Card*> pattern1,std::vector<Card*> pattern2) override;
    bool match(std::vector<Card*> cards) override;
    std::string GetPatternName() override;
};

#endif /* _FULLHOUSEHANDLER_H_ */

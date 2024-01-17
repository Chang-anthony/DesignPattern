#ifndef _SINGLEHANDLER_H_
#define _SINGLEHANDLER_H_

#include <CardPatternHandler.hpp>
class Card;


class SingleHandler : public CardPatternHandler
{
private:
    /* data */
    bool isBigger(std::vector<Card*> pattern1,std::vector<Card*> pattern2) override;
    bool match(std::vector<Card*> cards) override;
    std::string GetPatternName() override;

public:
    SingleHandler(CardPatternHandler* next);
    ~SingleHandler();
};




#endif /* _SINGLEHANDLER_H_ */

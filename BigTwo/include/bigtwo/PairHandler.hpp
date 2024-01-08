#ifndef _PAIRHANDLER_H_
#define _PAIRHANDLER_H_

#include <CardPatternHandler.hpp>
class Card;

class PairHandler:public CardPatternHandler
{
private:
    /* data */
public:
    PairHandler(CardPatternHandler* next);
    ~PairHandler();

    bool isBigger(std::vector<Card*> pattern1,std::vector<Card*> pattern2) override;
    bool match(std::vector<Card*> cards) override;
    std::string GetPatternName() override;
};

#endif /* _PAIRHANDLER_H_ */

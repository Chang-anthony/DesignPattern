#ifndef _STRAIGHTHANDLER_H_
#define _STRAIGHTHANDLER_H_

#include <CardPatternHandler.hpp>
class Card;

class StraightHandler : public CardPatternHandler
{
private:
    /* data */
public:
    StraightHandler(CardPatternHandler* next);
    ~StraightHandler();

    bool isBigger(std::vector<Card*> pattern1,std::vector<Card*> pattern2) override;
    bool match(std::vector<Card*> cards) override;
    std::string GetPatternName() override;
};

#endif /* _STRAIGHTHANDLER_H_ */

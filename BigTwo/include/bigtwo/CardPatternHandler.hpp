#ifndef _CARDPATTERNHANDLER_H_
#define _CARDPATTERNHANDLER_H_

class Card;
#include <vector>
#include <string>

//TODO:need to do
class CardPatternHandler
{
private:
    /* data */
    CardPatternHandler* next;
public:
    CardPatternHandler(CardPatternHandler* next);
    ~CardPatternHandler();

    bool vaild(std::vector<Card*> pattern1,std::vector<Card*> pattern2);

    virtual bool isBigger(std::vector<Card*> pattern1,std::vector<Card*> pattern2) = 0;
    virtual std::string matchtype(std::vector<Card*> cards) = 0;
};

#endif /* _CARDPATTERNHANDLER_H_ */

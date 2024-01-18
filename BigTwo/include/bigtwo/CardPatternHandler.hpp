#ifndef _CARDPATTERNHANDLER_H_
#define _CARDPATTERNHANDLER_H_

class Card;
#include <vector>
#include <string>


class CardPatternHandler
{
private:
    /* data */
    CardPatternHandler* next;
    virtual bool isBigger(std::vector<Card*> pattern1,std::vector<Card*> pattern2) = 0;
    virtual bool match(std::vector<Card*> cards) = 0;
    virtual std::string GetPatternName() = 0;

public:
    CardPatternHandler(CardPatternHandler* next);
    ~CardPatternHandler();

    bool isSamePatternHandle(std::vector<Card*> pattern1,std::vector<Card*> pattern2);
    std::string PatternNameHandle(std::vector<Card*> cards);
    bool BiggerHandle(std::vector<Card*> pattern1,std::vector<Card*> pattern2);
    bool vaild(std::vector<Card*> cards);
    void Render(std::string name);
};

#endif /* _CARDPATTERNHANDLER_H_ */

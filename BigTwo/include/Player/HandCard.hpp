#ifndef _HANDCARD_H_
#define _HANDCARD_H_

class Card;
#include <iostream>
#include <vector>
#include <string>


class HandCard
{
private:
    /* data */
    std::vector<Card*> handcard;
public:
    HandCard(/* args */);
    ~HandCard();

    void AddCard(Card* card);

    // setter
    void SetCards(std::vector<Card*> cards);

    //getter
    std::vector<Card*> GetCards();
};

#endif /* _HANDCARD_H_ */

#ifndef _HAND_H_
#define _HAND_H_

#include <iostream>
#include <vector>

class Card;

class Hand
{
private:
    /* data */
    std::vector<Card*> hand;
public:
    Hand(/* args */);
    ~Hand();

    //AddCard
    void AddCard(Card* card);

    //getter
    std::vector<Card*> GetHandCard();
    
    //setter
    void SetHandCard(std::vector<Card*> card);
};

#endif /* _HAND_H_ */

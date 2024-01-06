#ifndef _DECK_H_
#define _DECK_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

class Card;

class Deck
{
private:
    std::vector<Card*> cards;
public:
    Deck(/* args */);
    ~Deck();


    Card* DrawCard();
    void Suffle();
    void RenderCards();
    Deck* ReFresh();

    //getter
    std::vector<Card*> GetCards();

    //setter
    void SetCards(std::vector<Card*> cards);
};


#endif /* _DECK_H_ */

#ifndef _CARD_H_
#define _CARD_H_


#include "Rank.hpp"
#include "Suit.hpp"
class Deck;

class Card
{
private:
    Deck* deck;//此卡牌所屬的牌組
    Rank rank;
    Suit suit;
public:
    Card(Rank rank,Suit suit);
    Card(Rank rank,Suit suit,Deck* deck);
    ~Card();


    //Getter
    Rank GetRank();
    Suit GetSuit();
    Deck* GetDeck();

    //setter
    void SetRank(Rank rank);
    void SetSuit(Suit suit);
    void SetDeck(Deck* deck);

    void render();
};

#endif /* _CARD_H_ */

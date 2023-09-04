#ifndef _CARD_H_
#define _CARD_H_

// enum class Rank;
// enum class Suit;
#include "../include/Rank.hpp"
#include "../include/Suit.hpp"

class Card
{
private:
    Rank rank;
    Suit suit;
public:
    Card(Rank rank,Suit suit);
    ~Card();

    //Getter
    Rank GetRank();
    Suit GetSuit();

    //setter
    void SetRank(Rank rank);
    void SetSuit(Suit suit);

    void render();
    bool IsBigger(Card card);
};

#endif /* _CARD_H_ */

#ifndef _SHOWDOWNCARD_H_
#define _SHOWDOWNCARD_H_

// enum class Rank;
// enum class Suit;
#include "../include/Rank.hpp"
#include "../include/Suit.hpp"
#include "../include/Card.hpp"
class Deck;

class ShowDownCard:public Card
{
private:
    Deck* deck;//此卡牌所屬的牌組
    Rank rank;
    Suit suit;
public:
    ShowDownCard(Rank rank,Suit suit);
    ShowDownCard(Rank rank,Suit suit,Deck* deck);
    ~ShowDownCard();

    //Getter
    Rank GetRank();
    Suit GetSuit();
    Deck* GetDeck();

    //setter
    void SetRank(Rank rank);
    void SetSuit(Suit suit);
    void SetDeck(Deck* deck);

    void render() override;
    bool IsBigger(ShowDownCard* card);
};

#endif /* _SHOWDOWNCARD_H_ */

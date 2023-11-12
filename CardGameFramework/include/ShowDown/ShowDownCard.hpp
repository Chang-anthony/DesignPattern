#ifndef _SHOWDOWNCARD_H_
#define _SHOWDOWNCARD_H_

// enum class Rank;
// enum class Suit;
#include "../include/ShowDown/Rank.hpp"
#include "../include/ShowDown/Suit.hpp"
#include "../include/CardFramework/Card.hpp"

class ShowDownCard:public Card
{
private:
    Rank rank;
    Suit suit;
public:
    ShowDownCard(Rank rank,Suit suit);
    ~ShowDownCard();

    //Getter
    Rank GetRank();
    Suit GetSuit();
    static std::vector<Card*> GenCards();

    //setter
    void SetRank(Rank rank);
    void SetSuit(Suit suit);

    void render() override;
    bool IsBigger(ShowDownCard* card);
};

#endif /* _SHOWDOWNCARD_H_ */

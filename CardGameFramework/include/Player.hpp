#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <string>
#include <vector>

class Hand;
class Card;

class Player
{
private:
    /* data */
    std::string name;
    Hand* hand;
public:
    Player();
    ~Player();

    void AddCard(Card* card);
    virtual void NameSelf();
    virtual Card* takeTurn(std::vector<Card*> cards) = 0;

    //getter
    std::string GetName();
    Hand* GetHand();

    //setter
    void SetName(std::string name);
    void SetHand(Hand* hand);
};

#endif /* _PLAYER_H_ */

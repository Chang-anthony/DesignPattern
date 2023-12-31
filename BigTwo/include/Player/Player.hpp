#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>


class Card;
class Deck;
class HandCard;


class Player
{
private:
    /* data */
    HandCard* handcard;
    std::string name;
public:
    Player();
    ~Player();

    virtual void NameSelf() = 0;
    virtual std::vector<Card*> Play() = 0;
    void Deal(Deck* deck);

    //setter
    void SetHandCard(HandCard* hand);
    void SetName(std::string name);

    //getter
    HandCard* GetHandCard();
    std::string GetName();
};

#endif /* _PLAYER_H_ */

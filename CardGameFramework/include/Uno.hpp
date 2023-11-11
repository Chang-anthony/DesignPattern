#ifndef _UNO_H_
#define _UNO_H_

#include "../include/CardGame.hpp"
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "../include/utils/utils.h"

class Player;
class Deck;
class Card;

class Uno : public CardGame
{
private:
    /* data */
    Card* newCard;
    std::vector<Card*> passCards;
public:
    Uno(std::vector<Player*> players,Deck* deck);
    ~Uno();

    void Round() override;
    bool DrawCardEnd() override;
    bool IsGameEnd() override;
    Player* GetWinner() override;
    bool IsVaild(Card* card);
};

#endif /* _UNO_H_ */

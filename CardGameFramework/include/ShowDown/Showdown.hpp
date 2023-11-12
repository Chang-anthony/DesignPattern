#ifndef _SHOWDOWN_H_
#define _SHOWDOWN_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "../include/utils/utils.h"
#include "../include/CardFramework/CardGame.hpp"

class Player;
class Deck;
class Card;

class Showdown : public CardGame
{
private:
    /* data */
    int drawcardend;
    int round;
public:
    Showdown(std::vector<Player*> players,Deck* deck);
    ~Showdown();

    void Round() override;
    void Render(std::vector<Card*> cards);
    bool DrawCardEnd() override;
    bool IsGameEnd() override;
    Player* GetWinner() override;
    Player* Bigger(std::vector<Card*> cards);
};

#endif /* _SHOWDOWN_H_ */

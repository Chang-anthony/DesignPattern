#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include "../include/utils/utils.h"

class Card;
class Deck;
class ExchangeCard;

class Player
{
private:
    /* data */
    ExchangeCard* exchangecard;
    std::string name;
    std::vector<Card*> handcards;
    bool IsHuman;
    bool Exchange;//可否使用交換權
    int point;
public:
    Player(bool Human);
    ~Player();

    void NameSelf();
    void DrawCard(Deck* deck);
    virtual Card* ShowCard() = 0;
    void DoExchange(Player* player2);

    //getter
    std::string GetName();
    std::vector<Card*> GetHandCards();
    bool GetIsHuman();
    bool GetExchange();
    int GetPoint();
    ExchangeCard* GetExChangeCard();
    

    //setter
    void SetName(std::string name);
    void SetHandCards(std::vector<Card*> handcards);
    void SetIsHuman(bool ishuman);
    void SetExchange(bool exchange);
    void SetPoint(int point);
    void SetExChangeCard(ExchangeCard* exchangecard);

};

#endif /* _PLAYER_H_ */

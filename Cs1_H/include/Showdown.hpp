#ifndef _SHOWDOWN_H_
#define _SHOWDOWN_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "../include/utils/utils.h"

class Player;
class Deck;
class Card;

class Showdown
{
private:
    /* data */
    Deck* deck;
    std::vector<Player*> players;
public:
    Showdown(Deck* deck,std::vector<Player*> players);
    ~Showdown();

    void GameStart();
    void NameHimSelf();
    void DoShuffle();
    void DrawCard();
    void Round();
    void Render(std::vector<Card*> cards);
    Player* Bigger(std::vector<Card*> cards);
    void GameEnd();

    //getter
    Deck* GetDeck();
    std::vector<Player*> GetPlayers();

    //setter
    void SetDeck(Deck* deck);
    void SetPlayers(std::vector<Player*> players);
};

#endif /* _SHOWDOWN_H_ */

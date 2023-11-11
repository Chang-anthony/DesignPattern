#ifndef _CARDGAME_H_
#define _CARDGAME_H_

#include <iostream>
#include <vector>

class Player;
class Deck;
class Card;

class CardGame
{
private:
    /* data */
    std::vector<Player*> players;
    Deck* deck;
public:
    CardGame(std::vector<Player*> players,Deck* deck);
    ~CardGame();

    virtual void Round();
    virtual bool DrawCardEnd();
    virtual bool IsGameEnd();
    virtual Player* GetWinner();
    void GameEnd(Player* winner);
    void GameStart();


    //getter
    std::vector<Player*> GetPlayers();
    Deck* GetDeck();

    //setter
    void SetPlayers(std::vector<Player*> players);
    void SetDeck(Deck* deck);

};

#endif /* _CARDGAME_H_ */

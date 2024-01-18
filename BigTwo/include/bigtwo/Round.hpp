#ifndef _ROUND_H_
#define _ROUND_H_

#include <iostream>
#include <vector>
#include <utils.h>

class Player;
class Card;
class Bigtwo;

class Round
{
private:
    /* data */
    Bigtwo* game;
    std::vector<Card*> TopPlay;
    Player* TopPlayer;

public:
    Round(Player* TopPlayer,std::vector<Card*> TopPlay,Bigtwo* game);
    ~Round();

    //getter
    Player* GetTopPlayer();
    std::vector<Card*> GetTopPlay();
    Bigtwo* GetBigTwo();

    //setter
    void SetTopPlayer(Player* player);
    void SetTopPlay(std::vector<Card*> cards);
    void SetBigtwo(Bigtwo* game);

    Player* takeTurn(std::vector<Player*> players);
};

#endif /* _ROUND_H_ */

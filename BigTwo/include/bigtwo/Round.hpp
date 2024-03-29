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
    int pass;

    bool IsPass();

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

    static Round* newRound(Player* topplayer, Bigtwo *game);
    static std::pair<Round*, std::vector<std::vector<int>>> newRound(Player* topplayer, Bigtwo *game, std::vector<std::vector<int>> plays);

    Player* takeTurn(std::vector<Player*> players);
    //Test
    std::pair<Player*, std::vector<std::vector<int>>> takeTurn(std::vector<Player*> players, std::vector<std::vector<int>> plays);

protected:
    static bool condition(std::vector<Card*> cards);
};

#endif /* _ROUND_H_ */

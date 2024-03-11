#ifndef _FIRSTROUND_H_
#define _FIRSTROUND_H_

#include <iostream>
#include <vector>
#include <utils.h>
#include <Round.hpp>

class Player;
class Card;
class Bigtwo;


class FirstRound : public Round
{
private:
    /* data */
public:
    FirstRound(Player* TopPlayer, std::vector<Card*> TopPlay, Bigtwo* game);
    ~FirstRound();

    static FirstRound* newRound(Player* topplayer, Bigtwo *game);
    static std::pair<FirstRound*, std::vector<std::vector<int>>> newRound(Player* topplayer, Bigtwo *game, std::vector<std::vector<int>> plays);
    static bool condition(std::vector<Card*> cards);
};

#endif /* _FIRSTROUND_H_ */

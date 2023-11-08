#ifndef _AIPLAYER_H_
#define _AIPLAYER_H_

#include "../include/Player.hpp"

class Card;

class AIPlayer: public Player
{
private:
    /* data */
public:
    AIPlayer(/* args */);
    ~AIPlayer();
    Card* ShowCard() override;
};

#endif /* _AIPLAYER_H_ */

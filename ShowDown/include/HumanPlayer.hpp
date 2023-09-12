#ifndef _HUMANPLAYER_H_
#define _HUMANPLAYER_H_

#include "../include/Player.hpp"
class Card;

class HumanPlayer : public Player
{
private:
    /* data */
public:
    HumanPlayer(/* args */);
    ~HumanPlayer();
    Card* ShowCard() override;
};

#endif /* _HUMANPLAYER_H_ */

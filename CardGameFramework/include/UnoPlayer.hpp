#ifndef _UNOPLAYER_H_
#define _UNOPLAYER_H_

#include "../include/Player.hpp"
class Card;

class UnoPlayer : public Player
{
private:
    /* data */
public:
    UnoPlayer(/* args */);
    ~UnoPlayer();

    virtual Card* takeTurn(std::vector<Card*> cards) = 0;
};

#endif /* _UNOPLAYER_H_ */

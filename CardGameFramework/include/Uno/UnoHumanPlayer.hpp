#ifndef _UNOHUMANPLAYER_H_
#define _UNOHUMANPLAYER_H_

#include "../include/Uno/UnoPlayer.hpp"
class Card;

class UnoHumanPlayer:public UnoPlayer
{
private:
    /* data */
public:
    UnoHumanPlayer(/* args */);
    ~UnoHumanPlayer();

    Card* takeTurn(std::vector<Card*> cards) override;
};

#endif /* _UNOHUMANPLAYER_H_ */

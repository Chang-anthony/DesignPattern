#ifndef _UNOAIPLAYER_H_
#define _UNOAIPLAYER_H_

#include "../include/Uno/UnoPlayer.hpp"

class Card;

class UnoAIPlayer:public UnoPlayer
{
private:
    /* data */
public:
    UnoAIPlayer(/* args */);
    ~UnoAIPlayer();

    Card* takeTurn(std::vector<Card*> cards) override;
};

#endif /* _UNOAIPLAYER_H_ */

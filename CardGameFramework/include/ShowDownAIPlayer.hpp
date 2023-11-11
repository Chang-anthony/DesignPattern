#ifndef _SHOWDOWNAIPLAYER_H_
#define _SHOWDOWNAIPLAYER_H_

#include "../include/ShowDownPlayer.hpp"

class Card;

class ShowDownAIPlayer: public ShowDownPlayer
{
private:
    /* data */
public:
    ShowDownAIPlayer(/* args */);
    ~ShowDownAIPlayer();
    Card* takeTurn(std::vector<Card*> cards) override;
};

#endif /* _SHOWDOWNAIPLAYER_H_ */

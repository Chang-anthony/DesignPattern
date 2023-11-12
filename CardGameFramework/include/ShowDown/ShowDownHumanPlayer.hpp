#ifndef _SHOWDOWNHUMANPLAYER_H_
#define _SHOWDOWNHUMANPLAYER_H_

#include "../include/ShowDown/ShowDownPlayer.hpp"
class Card;

class ShowDownHumanPlayer : public ShowDownPlayer
{
private:
    /* data */
public:
    ShowDownHumanPlayer();
    ~ShowDownHumanPlayer();

    Card* takeTurn(std::vector<Card*> cards) override;
};

#endif /* _SHOWDOWNHUMANPLAYER_H_ */

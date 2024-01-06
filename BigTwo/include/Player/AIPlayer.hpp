#ifndef _AIPLAYER_H_
#define _AIPLAYER_H_

#include "Player.hpp"

class Card;

class AIPlayer: public Player
{
private:
    /* data */
public:
    AIPlayer(/* args */);
    ~AIPlayer();

    // TODO : need to implemntation
    void NameSelf() override;
    std::vector<Card*> Play() override;
};

#endif /* _AIPLAYER_H_ */

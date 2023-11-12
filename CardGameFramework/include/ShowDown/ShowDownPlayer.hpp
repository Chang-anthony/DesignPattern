#ifndef _SHOWDOWNPLAYER_H_
#define _SHOWDOWNPLAYER_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include "../include/CardFramework/Player.hpp"
#include "../include/utils/utils.h"

class Card;

class ShowDownPlayer : public Player
{
private:
    /* data */
    int point;
public:
    ShowDownPlayer();
    ~ShowDownPlayer();

    void gainPoint();
    virtual Card* takeTurn(std::vector<Card*> cards) = 0;

    //getter
    int GetPoint();
    
    //setter
    void SetPoint(int point);
};

#endif /* _SHOWDOWNPLAYER_H_ */

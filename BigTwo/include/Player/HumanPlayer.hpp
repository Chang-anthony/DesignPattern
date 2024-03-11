#ifndef _HUMANPLAYER_H_
#define _HUMANPLAYER_H_

#include <Player.hpp>

class Card;

class HumanPlayer : public Player
{
private:
    /* data */
public:
    HumanPlayer(/* args */);
    ~HumanPlayer();

    void NameSelf() override;
    std::vector<int> action() override;
};

#endif /* _HUMANPLAYER_H_ */

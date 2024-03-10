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
    std::vector<Card*> Play() override;
    std::vector<Card*> Play(std::vector<int> play) override;
};

#endif /* _HUMANPLAYER_H_ */

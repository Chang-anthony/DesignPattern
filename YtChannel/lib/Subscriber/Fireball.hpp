#ifndef _FIREBALL_H_
#define _FIREBALL_H_

#include <iostream>
#include "ChannelSubscriber.hpp"
class Channel;


class Fireball: public ChannelSubscriber
{
private:
    /* data */
public:
    Fireball();
    ~Fireball();

    void received(Channel* channel) override;
};

#endif /* _FIREBALL_H_ */

#ifndef _WATERBALL_H_
#define _WATERBALL_H_

#include <string>
#include <iostream>
#include "ChannelSubscriber.hpp"

class Channel;

class Waterball : public ChannelSubscriber
{
private:
    /* data */
public:
    Waterball();
    ~Waterball();

    void received(Channel* channel) override;
};

#endif /* _WATERBALL_H_ */

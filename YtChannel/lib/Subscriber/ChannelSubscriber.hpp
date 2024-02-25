#ifndef _CHANNELSUBSCRIBER_H_
#define _CHANNELSUBSCRIBER_H_

#include <iostream>
#include <vector>

class Video;
class Channel;


class ChannelSubscriber
{
private:
    /* data */
    std::vector<Channel*> channels;
public:
    ChannelSubscriber(/* args */);
    ~ChannelSubscriber();

    void subscribe(Channel* channel);
    void unsubsribe(Channel* target);
    virtual void received(Video* newVideo) = 0;

    //getter
    std::vector<Channel*> getChannels();

    //setter
    void setChannels(std::vector<Channel*> channels);
};

#endif /* _CHANNELSUBSCRIBER_H_ */

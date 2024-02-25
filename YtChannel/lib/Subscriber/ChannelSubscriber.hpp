#ifndef _CHANNELSUBSCRIBER_H_
#define _CHANNELSUBSCRIBER_H_

#include <iostream>
#include <vector>
#include <string>

class Channel;


class ChannelSubscriber
{
private:
    /* data */
    std::string name;
    std::vector<Channel*> channels;
public:
    ChannelSubscriber(std::string name);
    ~ChannelSubscriber();

    void subscribe(Channel* channel);
    void unsubsribe(Channel* target);
    virtual void received(Channel* channel) = 0;

    //getter
    std::vector<Channel*> getChannels();
    std::string getName();

    //setter
    void setChannels(std::vector<Channel*> channels);
    void setName(std::string name);
};

#endif /* _CHANNELSUBSCRIBER_H_ */

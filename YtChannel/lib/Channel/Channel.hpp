#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include <iostream>
#include <string>
#include <vector>

class Video;
class ChannelSubscriber;

class Channel
{
private:
    /* data */
    std::string name;
    std::vector<Video*> videos;
    std::vector<ChannelSubscriber*> subscribers;

public:
    Channel(std::string name);
    ~Channel();

    void moniter();
    void notifiy();
    void upload(Video* video);
    void AddSubscriber(ChannelSubscriber* subscriber);
    void RemoveSubscriber(ChannelSubscriber* target);

    //getter
    std::string getName();
    std::vector<Video*> getVideos();
    std::vector<ChannelSubscriber*> getSubscribers();

    //setter
    void setName(std::string name);
    void setVideos(std::vector<Video*> videos);
    void setSubscribers(std::vector<ChannelSubscriber*> subscribers);
};

#endif /* _CHANNEL_H_ */

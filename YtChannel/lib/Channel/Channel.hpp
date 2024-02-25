#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

class Video;
class ChannelSubscriber;

class Channel
{
private:
    /* data */
    std::thread moniterThread;
    std::mutex mutex;

    std::string name;
    std::vector<Video*> videos;
    std::vector<ChannelSubscriber*> subscribers;

public:
    Channel(std::string name);
    ~Channel();

    void startmoniter();
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
protected:
    int video_count = 0;
    bool monitoring = false;
    void moniter();
    void whenUploadVideo();
};

#endif /* _CHANNEL_H_ */

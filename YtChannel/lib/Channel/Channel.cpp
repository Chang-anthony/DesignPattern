#include <utils.hpp>
#include <Channel.hpp>
#include <Video.hpp>
#include <ChannelSubscriber.hpp>
#include <algorithm>


Channel::Channel(std::string name)
{
    this->setName(name);
    this->videos = std::vector<Video*>();
    this->subscribers = std::vector<ChannelSubscriber*>();
}

void Channel::moniter()
{

}

void Channel::notifiy()
{
    Video* newVideo = this->videos.back();
    for(auto scriber: this->getSubscribers())
        scriber->received(newVideo);
}

void Channel::upload(Video* video)
{
    utils::RequireNonNull(video);
    this->videos.push_back(video);
}

void Channel::AddSubscriber(ChannelSubscriber* subscriber)
{
    utils::RequireNonNull(subscriber);
    this->subscribers.push_back(subscriber);
}

void Channel::RemoveSubscriber(ChannelSubscriber* target)
{
    this->subscribers.erase(std::remove_if(this->subscribers.begin(), this->subscribers.end(),
    [target](ChannelSubscriber* remove){
        return remove == target;
    }),this->subscribers.end());
}

std::string Channel::getName()
{
    return this->name;
}

std::vector<Video*> Channel::getVideos()
{
    return this->videos;
}

std::vector<ChannelSubscriber*> Channel::getSubscribers()
{
    return this->subscribers;
}

void Channel::setName(std::string name)
{
    this->name = name;
}

void Channel::setVideos(std::vector<Video*> videos)
{
    utils::SizeShouldBigger(videos, 0);
    this->videos.clear();
    this->videos = videos;
}

void Channel::setSubscribers(std::vector<ChannelSubscriber*> subscribers)
{
    utils::SizeShouldBigger(subscribers, 0);
    this->subscribers.clear();
    this->subscribers = subscribers;
}

Channel::~Channel()
{
}

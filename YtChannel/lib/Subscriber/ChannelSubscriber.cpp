#include <ChannelSubscriber.hpp>
#include <Video.hpp>
#include <Channel.hpp>
#include <utils.hpp>
#include <algorithm>


ChannelSubscriber::ChannelSubscriber(/* args */)
{
    this->channels = std::vector<Channel*>();
}

void ChannelSubscriber::subscribe(Channel* channel)
{
    utils::RequireNonNull(channel);
    this->channels.push_back(channel);
    channel->AddSubscriber(this);
}

void ChannelSubscriber::unsubsribe(Channel* target)
{
    this->channels.erase(std::remove_if(this->channels.begin(), this->channels.end(),
    [target](Channel* remove){
        return remove == target;
    }),this->channels.end());
    target->RemoveSubscriber(this);
}

std::vector<Channel*> ChannelSubscriber::getChannels()
{
    return this->channels;
}

void ChannelSubscriber::setChannels(std::vector<Channel*> channels)
{
    utils::SizeShouldBigger(channels, 0);
    this->channels.clear();
    this->channels = channels;
}

ChannelSubscriber::~ChannelSubscriber()
{
}
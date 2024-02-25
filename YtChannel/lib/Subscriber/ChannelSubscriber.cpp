#include <ChannelSubscriber.hpp>
#include <Video.hpp>
#include <Channel.hpp>
#include <utils.hpp>
#include <algorithm>


ChannelSubscriber::ChannelSubscriber(std::string name)
{
    this->setName(name);
    this->channels = std::vector<Channel*>();
}

void ChannelSubscriber::subscribe(Channel* channel)
{
    utils::RequireNonNull(channel);
    std::cout << this->getName() << "訂閱了" << channel->getName() << "。" << std::endl;
    this->channels.push_back(channel);
    channel->AddSubscriber(this);
}

void ChannelSubscriber::unsubsribe(Channel* target)
{
    std::cout << this->getName() << "解除訂閱了" << target->getName() << "。" << std::endl;
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

std::string ChannelSubscriber::getName()
{
    return this->name;
}

void ChannelSubscriber::setChannels(std::vector<Channel*> channels)
{
    utils::SizeShouldBigger(channels, 0);
    this->channels.clear();
    this->channels = channels;
}

void ChannelSubscriber::setName(std::string name)
{
    this->name = name;
}

ChannelSubscriber::~ChannelSubscriber()
{
}
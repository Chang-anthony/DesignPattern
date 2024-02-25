#include <Fireball.hpp>
#include <Channel.hpp>
#include <Video.hpp>


Fireball::Fireball():ChannelSubscriber("火球")
{
}

void Fireball::received(Channel* channel)
{
    Video* newVideo = channel->getVideos().back();
    if(newVideo->getLength() <= 60)
    {
        std::cout << this->getName() << " 解除訂閱了 " << channel->getName() << "。" << std::endl;
        this->unsubsribe(channel);
    }
}

Fireball::~Fireball()
{
}
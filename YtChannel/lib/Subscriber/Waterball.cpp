#include <Waterball.hpp>
#include <Channel.hpp>
#include <Video.hpp>

Waterball::Waterball() : ChannelSubscriber("水球")
{
}

void Waterball::received(Channel* channel)
{
    Video* newVideo = channel->getVideos().back();
    if(newVideo->getLength() >= 180 )
        std::cout << this->getName() << " 對影片 " << newVideo->getTitle() << " 按讚。" << std::endl;
}

Waterball::~Waterball()
{
}
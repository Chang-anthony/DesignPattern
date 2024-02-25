#include <utils.hpp>
#include <Channel.hpp>
#include <Video.hpp>
#include <ChannelSubscriber.hpp>
#include <algorithm>
#include <chrono>



Channel::Channel(std::string name)
{
    this->setName(name);
    this->videos = std::vector<Video*>();
    this->subscribers = std::vector<ChannelSubscriber*>();
    this->video_count = 0;
    this->monitoring = false;
}

void Channel::startmoniter()
{
    this->monitoring = true;
    this->moniterThread = std::thread(&Channel::moniter, this);
}

// Need to fix
void Channel::moniter()
{

    while (this->monitoring)
    {
        try
        {
            whenUploadVideo();
            std::unique_lock<std::mutex> lock(mutex);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    
}

void Channel::whenUploadVideo()
{
    if(this->video_count < this->videos.size())
    {
        this->video_count = this->videos.size();
        this->notifiy();
    }
}

void Channel::notifiy()
{
    for(auto scriber: this->getSubscribers())
        scriber->received(this);
}

void Channel::upload(Video* video)
{
    utils::RequireNonNull(video);
    std::cout << "頻道 " << this->getName() << "上架了一則新影片 " << video->getTitle() << "。" << std::endl;
    this->videos.push_back(video);
    this->notifiy();
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

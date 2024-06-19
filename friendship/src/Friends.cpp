#include <Friends.hpp>
#include <utils.h>

Friends::Friends(/* args */)
{
    friends = std::vector<std::string>();
}

Friends::Friends(std::vector<std::string> friends)
{
    SetFriends(friends);
}

void Friends::AddFriend(std::string name)
{
    friends.push_back(name);
}

std::vector<std::string> Friends::GetFriends()
{
    return friends;
}

void Friends::SetFriends(std::vector<std::string> friends)
{
    utils::SizeShouldBigger(friends, 0);
    this->friends = friends;
}

Friends::~Friends()
{
}
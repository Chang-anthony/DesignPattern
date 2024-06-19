#ifndef _FRIENDS_H_
#define _FRIENDS_H_

#include <iostream>
#include <vector>
#include <map>
#include <string>

class Friends
{
private:
    /* data */
    std::vector<std::string> friends;
public:
    Friends();
    Friends(std::vector<std::string> friends);
    ~Friends();

    void AddFriend(std::string name);

    std::vector<std::string> GetFriends();

    void SetFriends(std::vector<std::string> friends);
};


#endif /* _FRIENDS_H_ */

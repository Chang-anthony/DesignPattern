#include "OnePunch.hpp"
#include <iostream>

OnePunch::OnePunch()
{
    setName("OnePunch");
    setMp(180);
    setTargetEnemy(1); // Target one enemy
    setTargetFriend(0); // No friend targeted
}

void OnePunch::attack(std::vector<Role*> roles)
{
    // TODO: Implement full attack algorithm for OnePunch
    std::cout << "OnePunch executed on one enemy with 180 MP." << std::endl;
}

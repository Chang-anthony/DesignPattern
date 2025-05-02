#include "OnePunch.hpp"
#include "OnePunchHandler.hpp"
#include "NormalHandler.hpp"
#include "CheerupHandler.hpp" 
#include "PoisonPetrochemicalHandler.hpp"
#include "HpHandler.hpp"
#include <iostream>

OnePunch::OnePunch()
{
    setName("OnePunch");
    setMp(180);
    setTargetEnemy(1); // Target one enemy
    setTargetFriend(0); // No friend targeted

    handler = new NormalHandler(new CheerupHandler(new PoisonPetrochemicalHandler(new HpHandler(nullptr))));
}


//TODO:
void OnePunch::attack(std::vector<Role*> roles)
{
    for (auto role : roles) {
        handler->handle(role);
    }
}


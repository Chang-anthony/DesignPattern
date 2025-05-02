#include "OnePunch.hpp"
#include "OnePunchHandler.hpp"
#include "NormalHandler.hpp"
#include "CheerupHandler.hpp" 
#include "PoisonPetrochemicalHandler.hpp"
#include "HpHandler.hpp"
#include <iostream>
#include "Role.hpp"

OnePunch::OnePunch() : Skill()
{
    setName("OnePunch");
    setMp(180);
    setTargetEnemy(1); // Target one enemy
    setTargetFriend(0); // No friend targeted

    handler = new HpHandler(new PoisonPetrochemicalHandler(new CheerupHandler(new NormalHandler(nullptr))));
}


void OnePunch::attack(Role* actor, std::vector<Role*> roles)
{
    for (auto role : roles) {
        handler->handle(role);
    }
}


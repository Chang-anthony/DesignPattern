#include "OnePunch.hpp"
#include "OnePunchHandler.hpp"
#include <iostream>
#include "Role.hpp"

OnePunch::OnePunch(std::vector<OnePunchHandler*> handlers) : Skill(), handlers(handlers)
{
    setName("一拳攻擊");
    setMp(180);
}


void OnePunch::attack(Role* actor, std::vector<Role*> roles)
{
    for (auto role : roles) {
        for (auto handler : handlers) {
            if (handler->handle(actor, role)) {
                break; // 只套用第一個成立的效果
            }
        }
    }
}


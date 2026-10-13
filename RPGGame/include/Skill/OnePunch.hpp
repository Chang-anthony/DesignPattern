#ifndef ONEPUNCH_HPP
#define ONEPUNCH_HPP

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration
class OnePunchHandler;

class OnePunch : public Skill
{
public:
    // 處理鏈由 Client 依序組好後注入；不提供預設鏈（D21、D23）
    OnePunch(std::vector<OnePunchHandler*> handlers);
    void attack(Role* actor, std::vector<Role*> roles) override;

protected:
    std::vector<OnePunchHandler*> handlers; // 由上而下比對，套用第一個成立的（D21）
};

#endif // ONEPUNCH_HPP

#ifndef _BASICATTACK_H_
#define _BASICATTACK_H_

#include "Skill.hpp"

class Role; // Forward declaration

class BasicAttack : public Skill
{
public:
    BasicAttack();
    ~BasicAttack() = default;

    void announce(Role* actor, const std::vector<Role*>& targets) const override;
    void attack(Role* actor, std::vector<Role*> roles) override;
};

#endif /* _BASICATTACK_H_ */

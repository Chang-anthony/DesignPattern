#ifndef _BASICATTACK_H_
#define _BASICATTACK_H_

#include "Skill.hpp"

class BasicAttack : public Skill
{
public:
    BasicAttack();
    ~BasicAttack() = default;

    void attack(std::vector<Role*> roles) override;
};

#endif /* _BASICATTACK_H_ */

#ifndef _CHEERUP_H_
#define _CHEERUP_H_

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class Cheerup : public Skill
{
public:
    Cheerup();
    void attack(Role* actor, std::vector<Role*> targets) override;
};

#endif /* _CHEERUP_H_ */

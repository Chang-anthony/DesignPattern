#ifndef _CHEERUP_H_
#define _CHEERUP_H_

#include "Skill.hpp"
#include <vector>

class Role; // Forward declaration

class Cheerup : public Skill
{
public:
    Cheerup();
    Candidates getCandidates(Role* actor, const std::vector<Role*>& t1,
                             const std::vector<Role*>& t2, int actorSide) const override;
    void attack(Role* actor, std::vector<Role*> targets) override;
};

#endif /* _CHEERUP_H_ */

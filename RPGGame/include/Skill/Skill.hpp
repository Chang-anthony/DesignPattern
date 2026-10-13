#ifndef _SKILL_H_
#define _SKILL_H_

#include <string>
#include <vector>
#include <iostream>
#include "../Role/Role.hpp"

class Role;

// 候選名單與要選的人數 m（D29）。取代原本的 targetEnemy / targetFriend
struct Candidates {
    std::vector<Role*> roles;
    int m;
};

class Skill
{
private:
    std::string name;
    int mp;

public:
    Skill();
    virtual ~Skill();

    // Getters 
    std::string getName() const;
    int getMp() const;

    // Setters
    void setName(const std::string& name);
    void setMp(int mp);

    // 算候選（D29、D33）：t1 / t2 為 Battle 給的兩軍名單（已排除死者），actorSide = 1 或 2（D31）；預設 = 1 位敵軍
    virtual Candidates getCandidates(Role* actor, const std::vector<Role*>& t1,
                                     const std::vector<Role*>& t2, int actorSide) const;
    // S3 的行動訊息：預設「X 對 a, b 使用了 名稱。」，沒有目標時「X 使用了 名稱。」
    virtual void announce(Role* actor, const std::vector<Role*>& targets) const;

    // Update the virtual function to accept two parameters
    // 每造成一次傷害就呼叫一次 actor->getState()->doDamage(target, n)（D16）
    virtual void attack(Role* actor, std::vector<Role*> targets) = 0;

protected:
    // D32：每個技能都會用到的敵友判斷
    static std::vector<Role*> enemiesOf(const std::vector<Role*>& t1, const std::vector<Role*>& t2, int actorSide);
    static std::vector<Role*> alliesOf(Role* actor, const std::vector<Role*>& t1,
                                       const std::vector<Role*>& t2, int actorSide); // 不含自己
    static std::vector<Role*> othersOf(Role* actor, const std::vector<Role*>& t1,
                                       const std::vector<Role*>& t2); // 全場（T1 → T2），不含自己
};

#endif /* _SKILL_H_ */

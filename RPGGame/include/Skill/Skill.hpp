#ifndef _SKILL_H_
#define _SKILL_H_

#include <string>
#include <vector>
#include <iostream>

class Role;

class Skill
{
private:
    std::string name;
    int mp;
    int targetEnemy;
    int targetFriend;

public:
    Skill();
    ~Skill();

    // Getters 
    std::string getName() const;
    int getMp() const;
    int getTargetEnemy() const;
    int getTargetFriend() const;

    // Setters
    void setName(const std::string& name);
    void setMp(int mp);
    void setTargetEnemy(int targetEnemy);
    void setTargetFriend(int targetFriend);

    virtual void attack(std::vector<Role*> roles) = 0;
};

#endif /* _SKILL_H_ */

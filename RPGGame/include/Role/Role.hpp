#ifndef ROLE_HPP
#define ROLE_HPP

#include <string>
#include <vector>

class State; // Forward declaration
class Skill; // Forward declaration

class Role {
private:
    int hp;
    int mp;
    int str;
    std::string name;
    State* state;
    std::vector<Skill*> skills;

public:
    Role(int hp, int mp, int str, const std::string& name);
    Role(int hp, int mp, int str, const std::string& name, const std::vector<Skill*>& skills);
    virtual ~Role();

    bool isDead() const;
    void damage(int damage);
    bool checkActionLossMp(int mpCost);
    void setState(State* newState);
    State* getState() const;
    void addSkill(Skill* skill);
    const std::vector<Skill*>& getSkills() const;
    int getHp() const;
    int getMp() const;
    int getStr() const;
    const std::string& getName() const;
};

#endif // ROLE_HPP

#ifndef ROLE_HPP
#define ROLE_HPP

#include <string>
#include <vector>
#include "../Observer/SkillObserver.hpp"
#include "../State/State.hpp" // Include State header

class Skill; // Forward declaration
class Troop;

class Role {
private:
    int hp;
    int mp;
    int str;
    std::string name;
    State* state; // One-to-one association with State
    std::vector<Skill*> skills;
    std::vector<SkillObserver*> observers; // Association with SkillObserver
    Troop* troop; // Association with Troop

public:
    Role(int hp, int mp, int str, const std::string& name);
    Role(int hp, int mp, int str, const std::string& name, const std::vector<Skill*>& skills);
    virtual ~Role();

    bool isDead() const;
    void lossHp(int damage); // HP 減少的唯一出口：歸零當下印死亡訊息並通知觀察者（D17）
    bool checkActionLossMp(int mpCost);
    void setState(State* newState);
    State* getState() const;
    void addSkill(Skill* skill);
    const std::vector<Skill*>& getSkills() const;
    int getHp() const;
    int getMp() const;
    int getStr() const;
    const std::string& getName() const;
    std::string getDisplayName() const; // 輸出用名稱，帶軍隊前綴，例如「[1]英雄」

    void lossMp(int mpCost);
    void gainMp(int mpGain);
    void gainHp(int hpGain);
    std::vector<SkillObserver*> getObservers();
    void addObserver(SkillObserver* observer);
    void removeObserver(SkillObserver* observer);
    void notifyObservers();

    void setTroop(Troop* troop);
    Troop* getTroop() const;
};

#endif // ROLE_HPP

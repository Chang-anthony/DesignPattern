#ifndef ROLE_HPP
#define ROLE_HPP

#include <string>
#include <vector>
#include "../Observer/SkillObserver.hpp"
#include "../State/State.hpp" // Include State header

class Skill; // Forward declaration
class Troop;
class IAction;

// 擁有權（D49）：Role 擁有自己的狀態、技能、觀察者與決策者，解構時一併釋放
class Role {
private:
    int hp;
    int mp;
    int str;
    std::string name;
    char identity; // 'h' = 英雄（D6），其他角色為 ' '
    State* state; // One-to-one association with State（擁有）
    std::vector<Skill*> skills; // 擁有
    std::vector<SkillObserver*> observers; // Association with SkillObserver（擁有，D49）
    Troop* troop; // Association with Troop（不擁有：Troop 擁有 Role）
    IAction* decider; // 決策者：英雄讀輸入、AI 依 seed（D4）；擁有（D49）

public:
    Role(int hp, int mp, int str, const std::string& name);
    Role(int hp, int mp, int str, const std::string& name, const std::vector<Skill*>& skills);
    virtual ~Role();
    Role(const Role&) = delete;            // 擁有裸指標：禁止複製，避免重複釋放
    Role& operator=(const Role&) = delete;

    // 輪到此角色時呼叫，交給目前的狀態主導這次行動（D10）；t1 / t2 為已排除死者的兩軍名單，actorSide = 1 或 2
    void takeTurn(const std::vector<Role*>& t1, const std::vector<Role*>& t2, int actorSide);

    bool isDead() const;
    bool checkMp(const Skill* skill) const; // S1：只檢查 MP 是否足夠，不扣除（D9）
    void setState(State* newState);
    State* getState() const;
    void endThisRound(); // 每回合結束由 Battle 呼叫：狀態回合數 −1，歸零時換回正常狀態（D11）
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
    void addObserver(SkillObserver* observer);       // 之後由 Role 釋放（D49）
    void removeObserver(SkillObserver* observer);    // 擁有權交回呼叫端
    void notifyObservers();

    void setTroop(Troop* troop);
    Troop* getTroop() const;

    void setDecider(IAction* decider); // 之後由 Role 釋放；換掉的舊決策者會被釋放（D49）
    IAction* getDecider() const;

    void setIdentity(char identity);
    char getIdentity() const;
    bool isHero() const; // identity == 'h'（D6）

private:
    // HP 減少的唯一出口：歸零當下印死亡訊息並通知觀察者（D17）。
    // 不公開（D47）：只有 State 能呼叫 —— 技能造成傷害一律走 actor->getState()->doDamage()，
    // 狀態自己扣血（中毒）走 State::damage()，行動的 HP 代價（自爆）由 State::decision() 依 Skill::costHp() 支付
    void lossHp(int damage);
    friend class State;
};

#endif // ROLE_HPP

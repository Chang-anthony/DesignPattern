#ifndef _SKILLOBSERVER_H_
#define _SKILLOBSERVER_H_

class Role; // Forward declaration

class SkillObserver {
protected:
    Role* actor; // Association with Role

public:
    SkillObserver(Role* actor);
    virtual ~SkillObserver() = default;

    // 被觀察的角色死亡時呼叫；pull model：只帶死者，需要的資料由觀察者自己讀（D18）
    virtual void UntilDie(Role* dead) = 0; // Pure virtual function

    void setRole(Role* associatedRole);
    Role* getRole();
};

#endif /* _SKILLOBSERVER_H_ */

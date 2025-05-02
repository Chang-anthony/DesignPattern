#ifndef _SKILLOBSERVER_H_
#define _SKILLOBSERVER_H_

class Role; // Forward declaration

class SkillObserver {
protected:
    Role* actor; // Association with Role

public:
    SkillObserver(Role* actor);
    virtual ~SkillObserver() = default;

    virtual void UntilDie() = 0; // Pure virtual function

    void setRole(Role* associatedRole);
    Role* getRole();
};

#endif /* _SKILLOBSERVER_H_ */

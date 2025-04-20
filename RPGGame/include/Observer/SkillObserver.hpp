#ifndef _SKILLOBSERVER_H_
#define _SKILLOBSERVER_H_

class Role; // Forward declaration

class SkillObserver {
protected:
    Role* role; // Association with Role

public:
    SkillObserver() : role(nullptr) {}
    SkillObserver(Role* associatedRole);
    virtual ~SkillObserver() = default;

    virtual void UntilDie() = 0; // Pure virtual function

    void setRole(Role* associatedRole);
    Role* getRole() const;
};

#endif /* _SKILLOBSERVER_H_ */

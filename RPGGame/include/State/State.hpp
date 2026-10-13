#ifndef STATE_HPP
#define STATE_HPP

#include <string>

class Role; // Forward declaration

class State {
private:
    int round;
    Role* role; // Association with Role

public:
    State(); // Default constructor
    State(Role* role); // Constructor with Role parameter
    virtual ~State();

    int getRound() const;
    void setRound(int round);

    Role* getRole() const;
    void setRole(Role* role);

    std::string getName() const; // Getter for className

    void entryState(State* newState);
    void exitState();

    // 行動者（擁有此狀態的角色）對 target 造成 n 點傷害：套用加成並印出傷害訊息（D16）
    virtual void doDamage(Role* target, int n);
    // 擁有此狀態的角色受到 n 點傷害，轉交 Role::lossHp()（D16、D17）
    virtual void damage(int n);

    // TODO: Implement the decision method in derived classes
    virtual void decision() = 0; // Pure virtual function

    friend class Role; // Add Role as a friend class

protected:
    std::string name; // Class name
};

#endif // STATE_HPP

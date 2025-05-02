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

    // TODO: Implement the decision method in derived classes
    virtual void decision() = 0; // Pure virtual function

    friend class Role; // Add Role as a friend class

protected:
    std::string name; // Class name
};

#endif // STATE_HPP

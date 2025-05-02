#ifndef _TROOP_H_
#define _TROOP_H_

#include <vector>
#include <memory>
class Battle; // Forward declaration
class Role;

class Troop {
private:
    std::vector<Role*> roles; // List of roles in the troop

public:
    Troop();
    ~Troop();

    std::vector<Role*> getRoles() const; // Get the list of roles
    void removeRole(Role* role); // Remove a role from the troop

    void addRole(Role* role); // Add a role to the troop
    bool Annihilated() const; // Check if all roles are dead
    Battle* StartBattle(Troop* enemy); // Create a Battle with an enemy troop
};

#endif /* _TROOP_H_ */

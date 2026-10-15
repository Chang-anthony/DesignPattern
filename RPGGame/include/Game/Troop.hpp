#ifndef _TROOP_H_
#define _TROOP_H_

#include <vector>
#include <memory>
class Role;

// 擁有權（D49）：Troop 擁有加入的角色（含戰鬥中召喚加入的），解構時一併釋放
class Troop {
private:
    int id; // 1 = T1、2 = T2；輸出名稱前綴「[1]」「[2]」
    std::vector<Role*> roles; // List of roles in the troop（擁有，D49）

public:
    Troop();
    Troop(int id);
    int getId() const;
    ~Troop(); // 釋放所有角色（D49）
    Troop(const Troop&) = delete;            // 擁有裸指標：禁止複製，避免重複釋放
    Troop& operator=(const Troop&) = delete;

    std::vector<Role*> getRoles() const; // Get the list of roles
    void removeRole(Role* role); // Remove a role from the troop（擁有權交回呼叫端）

    void addRole(Role* role); // Add a role to the troop（之後由 Troop 釋放）
    bool Annihilated() const; // Check if all roles are dead
};

#endif /* _TROOP_H_ */

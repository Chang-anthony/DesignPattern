#ifndef RPG_HPP
#define RPG_HPP

#include "../Role/Role.hpp"
#include <vector>
#include <memory>

class Troop; // Forward declaration
class Battle;
class Role;

class RPG {
private:
    Battle* battle; // Battle instance

public:
    RPG();
    ~RPG();

    void setBattle(Battle* battle);
    void GameStart(Troop* troop1, Troop* troop2);
    void GameEnd();

protected:
    void makeAction(Role* role);

};

#endif // RPG_HPP

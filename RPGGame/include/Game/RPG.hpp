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
    // 建立 Battle 並進行到結束，最後印「你獲勝了！」或「你失敗了！」（D1）；troop1 = T1（英雄所在）、troop2 = T2
    void GameStart(Troop* troop1, Troop* troop2);
    void GameEnd();

protected:
    void makeAction(Role* role);

};

#endif // RPG_HPP

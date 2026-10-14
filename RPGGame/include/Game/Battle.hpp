#ifndef BATTLE_HPP
#define BATTLE_HPP

#include <vector>

class Troop;
class Role;

// 兩軍之間的關聯類別（D1）：依 T1 → T2 輪流活著的角色、知道英雄是誰、判斷戰鬥是否結束
class Battle {
private:
    Troop* ally;  // Ally troop：T1（輸出前綴 [1]，英雄所在的軍隊）
    Troop* enemy; // Enemy troop：T2（輸出前綴 [2]）
    Role* hero;   // startBattle() 時從兩軍中找出 identity 為 'h' 的角色（D6）

    static std::vector<Role*> aliveRoles(const Troop* troop); // 依隊伍順序、排除死者（D30）
    Role* findHero() const;
    bool isEnd() const;   // 英雄死亡，或任一方被殲滅
    void endRound();      // 每回合結束：每位角色 endThisRound()（D11）

public:
    Battle(Troop* ally, Troop* enemy);
    ~Battle();

    // 一直進行回合直到戰鬥結束；找不到英雄時丟 std::invalid_argument
    void startBattle();
    // 戰鬥結束後由 RPG 判斷勝負：英雄活著 = 玩家獲勝
    bool isHeroAlive() const;
};

#endif // BATTLE_HPP

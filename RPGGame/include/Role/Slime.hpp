#ifndef SLIME_HPP
#define SLIME_HPP

#include "Role.hpp"
#include <string>

// 召喚出來的史萊姆（由 Summon 建立，AI 操控見 D40）；直接繼承 Role，非英雄由 identity 區分（D6、D43）
// 需求：史萊姆擁有 100 HP、0 MP、50 STR，沒有任何技能，初始為正常狀態 —— 這些數值由 Slime 自己持有（D44）
class Slime : public Role {
public:
    Slime(); // 名稱 "Slime"、100 HP、0 MP、50 STR；技能只有 Role 自動加入的普通攻擊（D28）

    // Additional methods or attributes specific to Slime can be added here
};

#endif // SLIME_HPP

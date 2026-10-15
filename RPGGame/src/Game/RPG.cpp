#include "RPG.hpp"
#include "Battle.hpp"
#include "Troop.hpp"
#include "Role.hpp"
#include <iostream>
#include "Output.hpp"
#include "../utils/utils.h"

RPG::RPG() : battle(nullptr) {}

RPG::~RPG() {}

void RPG::setBattle(Battle* battle) {
    this->battle = utils::RequireNonNull(battle);
}

void RPG::GameStart(Troop* troop1, Troop* troop2)
{
    utils::RequireNonNull(troop1);
    utils::RequireNonNull(troop2);

    battle = new Battle(troop1, troop2);
    battle->startBattle();

    // 戰鬥結束：英雄活著 → 玩家獲勝（需求「輸出格式」最後一行）
    io::output().write(battle->isHeroAlive() ? "你獲勝了！" : "你失敗了！"); // 輸出經由 utils（D50）
}

void RPG::GameEnd() {
    if (battle) {
        delete battle;
        battle = nullptr;
    }
}



#include "RPG.hpp"
#include "Battle.hpp"
#include "Troop.hpp"
#include "Role.hpp"
#include <iostream>
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
}

//TODO:
void RPG::makeAction(Role* role) {
}

void RPG::GameEnd() {
    if (battle) {
        delete battle;
        battle = nullptr;
    }
}



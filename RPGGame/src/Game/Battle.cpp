#include "Battle.hpp"
#include "Troop.hpp"
#include <iostream>
#include "../utils/utils.h"

Battle::Battle(Troop* ally, Troop* enemy)
    : ally(utils::RequireNonNull(ally)), enemy(utils::RequireNonNull(enemy)) {}

Battle::~Battle() {}

//TODO
void Battle::startBattle() {
    
}


#include "Battle.hpp"
#include "Troop.hpp"
#include "Role.hpp"
#include <iostream>
#include <stdexcept>
#include "../utils/utils.h"

Battle::Battle(Troop* ally, Troop* enemy)
    : ally(utils::RequireNonNull(ally)), enemy(utils::RequireNonNull(enemy)), hero(nullptr) {}

Battle::~Battle() {}

std::vector<Role*> Battle::aliveRoles(const Troop* troop) {
    std::vector<Role*> alive;
    for (Role* role : troop->getRoles()) {
        if (!role->isDead()) {
            alive.push_back(role);
        }
    }
    return alive;
}

Role* Battle::findHero() const {
    for (const Troop* troop : {ally, enemy}) {
        for (Role* role : troop->getRoles()) {
            if (role->isHero()) {
                return role;
            }
        }
    }
    return nullptr;
}

bool Battle::isEnd() const {
    return hero->isDead() || ally->Annihilated() || enemy->Annihilated();
}

void Battle::endRound() {
    for (const Troop* troop : {ally, enemy}) {
        for (Role* role : troop->getRoles()) {
            role->endThisRound();
        }
    }
}

void Battle::startBattle() {
    hero = findHero();
    if (hero == nullptr) {
        throw std::invalid_argument("Battle: no hero (identity 'h') in either troop");
    }

    while (!isEnd()) {
        // 一回合：T1 全部輪完再換 T2（D1、D20）
        for (int side = 1; side <= 2; side++) {
            Troop* troop = side == 1 ? ally : enemy;
            // 用索引走訪且每圈重讀人數：本回合召喚、加入隊尾的史萊姆也會輪到（D20）
            for (size_t i = 0; i < troop->getRoles().size(); i++) {
                Role* role = troop->getRoles()[i];
                if (role->isDead()) {
                    continue; // 不會輪到已死亡的角色
                }
                // 交給行動流程的是兩軍「活著的」名單 + 行動者屬於哪一軍（D30、D31）
                role->takeTurn(aliveRoles(ally), aliveRoles(enemy), side);
                if (isEnd()) {
                    return; // 每次行動後檢查：英雄死亡或任一方殲滅 → 戰鬥立即結束
                }
            }
        }
        endRound();
    }
}

bool Battle::isHeroAlive() const {
    return hero != nullptr && !hero->isDead();
}

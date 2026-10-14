#include "Role.hpp"
#include "Skill.hpp"
#include "SkillObserver.hpp"
#include "../State/State.hpp"
#include "../State/NormalState.hpp"
#include "BasicAttack.hpp"
#include "Troop.hpp"
#include <iostream>
#include "../utils/utils.h"

//TODO: Implement the State class and its methods
Role::Role(int hp, int mp, int str, const std::string& name)
    : hp(hp), mp(mp), str(str), name(name), identity(' '), state(new NormalState()), troop(nullptr), decider(nullptr) { // Default state is NormalState
    state->setRole(this);
    skills.insert(skills.begin(), new BasicAttack()); // 普通攻擊固定在第 0 項（D28）
}

Role::Role(int hp, int mp, int str, const std::string& name, const std::vector<Skill*>& skills)
    : hp(hp), mp(mp), str(str), name(name), identity(' '), state(new NormalState()), skills(skills), troop(nullptr), decider(nullptr) { // Default state is NormalState
    state->setRole(this);
    this->skills.insert(this->skills.begin(), new BasicAttack()); // 普通攻擊固定在第 0 項（D28）
}

Role::~Role() {
    delete state;
    for (Skill* skill : skills) {
        delete skill;
    }
}

void Role::takeTurn(const std::vector<Role*>& t1, const std::vector<Role*>& t2, int actorSide) {
    // 「輪到 …」在狀態效果之前印：石化也要印、中毒印的是扣 30 之前的 HP（§7.2 I6，對照 testcases/poison.out）
    std::cout << "輪到 " << getDisplayName() << " (HP: " << hp << ", MP: " << mp << ", STR: " << str
              << ", State: " << state->getDisplayName() << ")。" << std::endl;
    state->decision(t1, t2, actorSide);
}

bool Role::isDead() const {
    return hp <= 0;
}

void Role::lossHp(int damage) {
    bool wasAlive = !isDead();
    hp -= damage;
    if (hp < 0) hp = 0;
    if (wasAlive && isDead()) {
        std::cout << getDisplayName() << " 死亡。" << std::endl;
        notifyObservers();
    }
}

bool Role::checkMp(const Skill* skill) const {
    return mp >= utils::RequireNonNull(skill)->getMp();
}

void Role::setState(State* newState) {
    if (state) {
        state->exitState();
        delete state;
    }
    state = utils::RequireNonNull(newState);
    state->setRole(this);
    state->entryState(newState);
}

State* Role::getState() const {
    return state;
}

void Role::endThisRound() {
    if (state->getRound() <= 0) {
        return; // 沒有時效的狀態（正常狀態）
    }
    state->setRound(state->getRound() - 1);
    if (state->getRound() == 0) {
        setState(new NormalState()); // 由 Role 換狀態，避免 State 在自己的函式內被 delete（D11）
    }
}

void Role::addSkill(Skill* skill) {
    utils::RequireNonNull(skill);
    skills.push_back(skill);
}

const std::vector<Skill*>& Role::getSkills() const {
    return skills;
}

int Role::getHp() const {
    return hp;
}

int Role::getMp() const {
    return mp;
}

int Role::getStr() const {
    return str;
}

void Role::lossMp(int mpCost) {
    mp -= mpCost;
    if (mp < 0) mp = 0;
}

void Role::gainMp(int mpGain) {
    mp += mpGain;
}

void Role::gainHp(int hpGain) {
    hp += hpGain;
}

const std::string& Role::getName() const {
    return name;
}

std::string Role::getDisplayName() const {
    if (troop == nullptr) {
        return name;
    }
    return "[" + std::to_string(troop->getId()) + "]" + name;
}

std::vector<SkillObserver*> Role::getObservers() {
    return observers;
}

void Role::addObserver(SkillObserver* observer) {
    utils::RequireNonNull(observer);
    observers.push_back(observer);
}

void Role::removeObserver(SkillObserver* observer) {
    observers = utils::RemoveObjectFromVector(observers, observer);
}

void Role::notifyObservers() {
    for (SkillObserver* observer : observers) {
        observer->UntilDie(this); // pull model：只交出死者（D18）
    }
}

// troop 可為 nullptr：代表角色離開軍隊（Troop::removeRole 會這樣呼叫）
void Role::setTroop(Troop* troop) {
    this->troop = troop;
}

Troop* Role::getTroop() const {
    return troop;
}

void Role::setDecider(IAction* decider) {
    this->decider = utils::RequireNonNull(decider);
}

IAction* Role::getDecider() const {
    return decider;
}

void Role::setIdentity(char identity) {
    this->identity = identity;
}

char Role::getIdentity() const {
    return identity;
}

bool Role::isHero() const {
    return identity == 'h';
}

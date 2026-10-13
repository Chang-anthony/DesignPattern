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
    : hp(hp), mp(mp), str(str), name(name), state(new NormalState()), troop(nullptr) { // Default state is NormalState
    state->setRole(this);
    skills.insert(skills.begin(), new BasicAttack()); // 普通攻擊固定在第 0 項（D28）
}

Role::Role(int hp, int mp, int str, const std::string& name, const std::vector<Skill*>& skills)
    : hp(hp), mp(mp), str(str), name(name), state(new NormalState()), skills(skills), troop(nullptr) { // Default state is NormalState
    state->setRole(this);
    this->skills.insert(this->skills.begin(), new BasicAttack()); // 普通攻擊固定在第 0 項（D28）
}

Role::~Role() {
    delete state;
    for (Skill* skill : skills) {
        delete skill;
    }
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

bool Role::checkActionLossMp(int mpCost) {
    if (mp < mpCost) {
        std::cout << name << " does not have enough MP to perform the action." << std::endl;
        return false;
    } else {
        mp -= mpCost;
        return true;
    }
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

void Role::setTroop(Troop* troop) {
    utils::RequireNonNull(troop);
    this->troop = troop;
}

Troop* Role::getTroop() const {
    return troop;
}

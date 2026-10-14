#include "State.hpp"
#include <iostream>
#include "utils.h"
#include "Role.hpp"
#include "Skill.hpp"
#include "IAction.hpp"

State::State() : round(0), role(nullptr), name(""), displayName("") {} // Default constructor

State::State(Role* role) :
    round(0), role(utils::RequireNonNull(role)), name("State"), displayName("") {} // Constructor with Role parameter

State::~State() {}

int State::getRound() const {
    return round;
}

void State::setRound(int round) {
    this->round = round;
}

Role* State::getRole() const {
    return role;
}

void State::setRole(Role* role) {
    utils::RequireNonNull(role);
    this->role = role;
}

std::string State::getName() const {
    return name;
}

std::string State::getDisplayName() const {
    return displayName;
}

void State::entryState(State* newState) {
    utils::RequireNonNull(newState);
}

void State::exitState() {
}

void State::doDamage(Role* target, int n) {
    utils::RequireNonNull(target);
    std::cout << utils::RequireNonNull(role)->getDisplayName() << " 對 " << target->getDisplayName()
              << " 造成 " << n << " 點傷害。" << std::endl;
    utils::RequireNonNull(target->getState())->damage(n);
}

void State::damage(int n) {
    utils::RequireNonNull(role)->lossHp(n);
}

namespace {

// S1 的提示：「選擇行動：(0) 普通攻擊 (1) 火球 …」，每個角色都會印（含 AI）
void printActionMenu(const std::vector<Skill*>& skills) {
    std::cout << "選擇行動：";
    for (size_t i = 0; i < skills.size(); i++) {
        if (i > 0) {
            std::cout << " ";
        }
        std::cout << "(" << i << ") " << skills[i]->getName();
    }
    std::cout << std::endl;
}

} // namespace

void State::decision(const std::vector<Role*>& t1, const std::vector<Role*>& t2, int actorSide) {
    Role* actor = utils::RequireNonNull(role);
    IAction* decider = utils::RequireNonNull(actor->getDecider());

    // S1：選行動；MP 不足 → 印訊息並重新選擇（D5、D9）
    Skill* skill = nullptr;
    while (true) {
        printActionMenu(actor->getSkills());
        skill = utils::RequireNonNull(decider->chooseAction(actor->getSkills()));
        if (actor->checkMp(skill)) {
            break;
        }
        std::cout << "你缺乏 MP，不能進行此行動。" << std::endl;
    }

    // S2：技能算候選（D29），決策者選目標；n ≤ m 自動全選由決策者判斷（D8）
    Candidates candidates = skill->getCandidates(actor, t1, t2, actorSide);
    std::vector<Role*> targets = decider->chooseTargets(candidates.roles, candidates.m);

    // S3：先扣 MP，再印行動訊息並執行（D9、§7.2 I1）
    actor->lossMp(skill->getMp());
    skill->announce(actor, targets);
    skill->attack(actor, targets);
}

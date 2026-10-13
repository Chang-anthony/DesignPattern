#include "Skill.hpp"
#include "utils.h"

// Constructor and Destructor
Skill::Skill() = default;
Skill::~Skill() = default;

// Getters
std::string Skill::getName() const { return name; }
int Skill::getMp() const { return mp; }

// Setters
void Skill::setName(const std::string& name) { this->name = name; }
void Skill::setMp(int mp) { this->mp = mp; }

// 預設：1 位敵軍（D33）
Candidates Skill::getCandidates(Role* actor, const std::vector<Role*>& t1,
                                const std::vector<Role*>& t2, int actorSide) const {
    return {enemiesOf(t1, t2, actorSide), 1};
}

void Skill::announce(Role* actor, const std::vector<Role*>& targets) const {
    utils::RequireNonNull(actor);
    if (targets.empty()) {
        std::cout << actor->getDisplayName() << " 使用了 " << name << "。" << std::endl;
        return;
    }
    std::cout << actor->getDisplayName() << " 對 ";
    for (size_t i = 0; i < targets.size(); i++) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << targets[i]->getDisplayName();
    }
    std::cout << " 使用了 " << name << "。" << std::endl;
}

std::vector<Role*> Skill::enemiesOf(const std::vector<Role*>& t1, const std::vector<Role*>& t2, int actorSide) {
    return actorSide == 1 ? t2 : t1;
}

std::vector<Role*> Skill::alliesOf(Role* actor, const std::vector<Role*>& t1,
                                   const std::vector<Role*>& t2, int actorSide) {
    return utils::RemoveObjectFromVector(actorSide == 1 ? t1 : t2, actor);
}

std::vector<Role*> Skill::othersOf(Role* actor, const std::vector<Role*>& t1, const std::vector<Role*>& t2) {
    std::vector<Role*> all = t1;
    all.insert(all.end(), t2.begin(), t2.end());
    return utils::RemoveObjectFromVector(all, actor);
}

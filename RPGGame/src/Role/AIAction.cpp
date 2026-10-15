#include "AIAction.hpp"
#include <stdexcept>

AIAction::AIAction(int seed) : seed(seed) {}

Skill* AIAction::chooseAction(const std::vector<Skill*>& skills) {
    if (skills.empty()) {
        throw std::invalid_argument("AIAction::chooseAction: no action to choose");
    }
    Skill* chosen = skills[seed % skills.size()];
    seed++;
    return chosen;
}

std::vector<Role*> AIAction::chooseTargets(const std::vector<Role*>& candidates, int m) {
    int n = static_cast<int>(candidates.size());
    if (m <= 0 || n <= m) {
        return candidates; // 略過 S2：自動全選，不是 AI 做的決策（D8，已用 waterball-and-fireball-1v2 驗證）
    }
    std::vector<Role*> targets;
    for (int i = 0; i < m; i++) {
        targets.push_back(candidates[(seed + i) % n]);
    }
    seed++;
    return targets;
}

int AIAction::getSeed() const {
    return seed;
}

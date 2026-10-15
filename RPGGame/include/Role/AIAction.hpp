#ifndef AIACTION_HPP
#define AIACTION_HPP

#include "IAction.hpp"

// AI 決策者：每做完一個決策 seed + 1（需求「AI 決策」章節）
class AIAction : public IAction {
private:
    int seed; // 初始值 0

public:
    explicit AIAction(int seed = 0);

    // S1：選第 seed % 行動數 個，之後 seed + 1
    Skill* chooseAction(const std::vector<Skill*>& skills) override;
    // S2：n > m 時選 u[s % n], u[(s + 1) % n], …, u[(s + m - 1) % n]，全部選完 seed 才 + 1；
    //     m = 0 或 n ≤ m 時直接回傳全部候選，不算一次決策，seed 不變
    std::vector<Role*> chooseTargets(const std::vector<Role*>& candidates, int m) override;

    int getSeed() const;
};

#endif // AIACTION_HPP

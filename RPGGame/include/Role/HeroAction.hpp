#ifndef HEROACTION_HPP
#define HEROACTION_HPP

#include <istream>
#include <vector>
#include "IAction.hpp"

// 英雄的決策者（D4、D37）：每個決策讀輸入的一行，S1 與 S2 共用同一串輸入
//   - 一行是以「, 」（逗號加一個空白）隔開的數字，例如 "1" 或 "0, 1, 2"
//   - 正式執行注入 std::cin，測試注入讀測資檔的 stream
class HeroAction : public IAction {
private:
    std::istream& input;

    std::vector<int> readDecision(); // 讀下一個非空白行並解析成數字

public:
    explicit HeroAction(std::istream& input);

    // S1：讀一行，選第 i 個行動；MP 不足時呼叫端會再呼叫一次 → 讀下一行
    Skill* chooseAction(const std::vector<Skill*>& skills) override;
    // S2：n > m 時先印「選擇 m 位目標: (0) … (1) …」，再讀一行 m 個數字，依輸入順序回傳對應的候選；
    //     m = 0 或 n ≤ m 時直接回傳全部候選，**不讀輸入**（略過 S2，D8）
    std::vector<Role*> chooseTargets(const std::vector<Role*>& candidates, int m) override;
};

#endif // HEROACTION_HPP

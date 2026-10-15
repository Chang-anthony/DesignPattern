#ifndef _IACTION_H_
#define _IACTION_H_

#include <vector>

class Skill;
class Role;

// 決策者（Strategy，D4）：只負責 S1、S2 兩個決策，不執行行動
class IAction {
public:
    virtual ~IAction() = default;

    // S1：從行動清單選一個行動（D5）；MP 是否足夠由呼叫端用 Role::checkMp() 檢查，不足會再呼叫一次
    virtual Skill* chooseAction(const std::vector<Skill*>& skills) = 0;

    // S2：從候選中選 m 位（D7）；m = 0 或 n ≤ m 時自動回傳全部候選、略過 S2，也由實作判斷（D8）
    virtual std::vector<Role*> chooseTargets(const std::vector<Role*>& candidates, int m) = 0;
};

#endif /* _IACTION_H_ */

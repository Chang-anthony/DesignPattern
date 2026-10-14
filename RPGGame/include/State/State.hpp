#ifndef STATE_HPP
#define STATE_HPP

#include <string>
#include <vector>

class Role; // Forward declaration

class State {
private:
    int round;
    Role* role; // Association with Role

public:
    State(); // Default constructor
    State(Role* role); // Constructor with Role parameter
    virtual ~State();

    int getRound() const;
    void setRound(int round);

    Role* getRole() const;
    void setRole(Role* role);

    std::string getName() const; // Getter for className
    std::string getDisplayName() const; // 輸出用的中文名稱：正常 / 石化 / 中毒 / 受到鼓舞（「輪到 …」那一行用）

    void entryState(State* newState);
    void exitState();

    // 行動者（擁有此狀態的角色）對 target 造成 n 點傷害：套用加成並印出傷害訊息（D16）
    // 技能造成傷害的唯一通道（D47）
    virtual void doDamage(Role* target, int n);

    // 一次行動的預設流程（D10、D12）：S1 選行動（MP 不足就印訊息並重選）→ S2 算候選、選目標 → S3 扣 MP、印行動訊息、執行
    //   t1 / t2 為已排除死者的兩軍名單，actorSide = 1 或 2（D30、D31）
    //   各狀態只覆寫不同的部分：石化 → 整段跳過；中毒 → 先扣 30 HP、活著才走這個預設流程
    virtual void decision(const std::vector<Role*>& t1, const std::vector<Role*>& t2, int actorSide);

    friend class Role; // Add Role as a friend class

protected:
    // 擁有此狀態的角色受到 n 點傷害（不印訊息），轉交 Role::lossHp()（D16、D17）。
    // 不公開（D47）：只能經由 doDamage()，或由狀態自己呼叫（例如中毒扣 30）
    virtual void damage(int n);

    std::string name;        // Class name
    std::string displayName; // 中文名稱，由各狀態在建構子設定（新增狀態不必改 State，需求 ③）
};

#endif // STATE_HPP

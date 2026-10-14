#ifndef _RPG_PARSER_H_
#define _RPG_PARSER_H_

#include <istream>
#include <string>

class Troop;
class Role;
class Skill;

// 解析結果：兩軍與英雄（英雄的決策者由呼叫端決定要讀哪個輸入，D37）
struct RPGSetup {
    Troop* t1;   // 軍隊 1，編號 1（輸出前綴 [1]）
    Troop* t2;   // 軍隊 2，編號 2（輸出前綴 [2]）
    Role* hero;  // T1 的第一位角色，已 setIdentity('h')；decider 尚未設定
};

// Client 端的輸入解析（D26、D36）：屬於模組外部，技能名稱 → Skill 的對應只寫在這裡
class RPG_parser {
public:
    // 讀「#軍隊-1-開始 … #軍隊-1-結束 #軍隊-2-開始 … #軍隊-2-結束」並建立兩軍。
    //   - 每行：<名稱> <HP> <MP> <STR> [技能 …]（以空白分隔）；普通攻擊由 Role 自動加入（D28）
    //   - T1 第一位標成英雄（D6）；其他角色都裝上 AIAction（需求：英雄以外由 AI 操控）
    //   - 讀到「#軍隊-2-結束」就停止：input 剩下的就是英雄決策，可直接交給 HeroAction（D37）
    //   - 格式錯誤（缺少區段、數值錯誤、未知技能、T1 沒有角色）丟 std::invalid_argument
    static RPGSetup parse(std::istream& input);

    // 中文技能名稱 → 技能物件（D26）；一拳攻擊注入需求順序的處理鏈（D21）。未知名稱丟 std::invalid_argument
    static Skill* createSkill(const std::string& name);
};

#endif /* _RPG_PARSER_H_ */

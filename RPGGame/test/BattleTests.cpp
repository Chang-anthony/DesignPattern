/*
 * Battle 與 RPG 的單元測試。
 *  - 依據：need/need.md「遊戲流程」「輸出格式」、CLAUDE.md 決策 D1、D6、D11、D20、D30、D31
 *  - 每個情境都設計成會自然結束（英雄死亡或一方殲滅），英雄的決策用 istringstream 提供
 */
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Output.hpp"
#include "Battle.hpp"
#include "RPG.hpp"
#include "Troop.hpp"
#include "Role.hpp"
#include "AIAction.hpp"
#include "HeroAction.hpp"
#include "Summon.hpp"
#include "Poison.hpp"

namespace {

using Lines = std::vector<std::string>;

// 在作用域內把模組輸出（io::output()）導向字串，解構時還原（D50）
class OutputCapture {
public:
    OutputCapture() : sink(buffer), previous(io::setOutput(&sink)) {}
    ~OutputCapture() { io::setOutput(previous); }

    Lines lines() const {
        Lines result;
        std::istringstream in(buffer.str());
        std::string line;
        while (std::getline(in, line)) result.push_back(line);
        return result;
    }

private:
    std::ostringstream buffer;
    io::StreamOutput sink;
    io::Output* previous;
};

// 只留下「輪到 …」的行，用來檢查輪流順序
Lines turnHeaders(const Lines& lines) {
    Lines headers;
    for (const std::string& line : lines) {
        if (line.rfind("輪到 ", 0) == 0) headers.push_back(line);
    }
    return headers;
}

int countLinesStartingWith(const Lines& lines, const std::string& prefix) {
    int count = 0;
    for (const std::string& line : lines) {
        if (line.rfind(prefix, 0) == 0) count++;
    }
    return count;
}

class BattleTest : public ::testing::Test {
protected:
    std::istringstream heroInput; // 宣告在 Troop 之前：角色（含英雄的 HeroAction）先釋放
    Troop t1{1};
    Troop t2{2};

    Role* addHero(int hp, int mp, int str, const std::string& decisions, const std::vector<Skill*>& skills = {}) {
        Role* hero = new Role(hp, mp, str, "英雄", skills);
        hero->setIdentity('h');
        heroInput.str(decisions);
        hero->setDecider(new HeroAction(heroInput)); // Role 擁有決策者（D49）
        t1.addRole(hero);
        return hero;
    }

    Role* addAI(Troop& troop, const std::string& name, int hp, int mp, int str) {
        Role* role = new Role(hp, mp, str, name);
        role->setDecider(new AIAction());
        troop.addRole(role);
        return role;
    }

    Lines runBattle(Battle& battle) {
        OutputCapture capture;
        battle.startBattle();
        return capture.lines();
    }
};

// =====================================================================
// 英雄（D6）
// =====================================================================

TEST_F(BattleTest, RequiresAHero) {
    addAI(t1, "A", 100, 0, 10);
    addAI(t2, "B", 100, 0, 10);
    Battle battle(&t1, &t2);
    EXPECT_THROW(battle.startBattle(), std::invalid_argument);
}

TEST_F(BattleTest, RejectsMissingTroops) {
    EXPECT_THROW(Battle(nullptr, &t2), std::invalid_argument);
    EXPECT_THROW(Battle(&t1, nullptr), std::invalid_argument);
}

// =====================================================================
// 結束條件：每次行動後檢查（需求「當 S3 結束後檢查」）
// =====================================================================

TEST_F(BattleTest, EndsAsSoonAsEnemyTroopIsAnnihilated) {
    addHero(500, 0, 100, "0\n");
    Role* slime = addAI(t2, "Slime1", 100, 0, 999);
    Battle battle(&t1, &t2);

    EXPECT_EQ(runBattle(battle), (Lines{
        "輪到 [1]英雄 (HP: 500, MP: 0, STR: 100, State: 正常)。",
        "選擇行動：(0) 普通攻擊",
        "[1]英雄 攻擊 [2]Slime1。",
        "[1]英雄 對 [2]Slime1 造成 100 點傷害。",
        "[2]Slime1 死亡。",
    }));
    EXPECT_TRUE(slime->isDead());
    EXPECT_TRUE(battle.isHeroAlive());
}

TEST_F(BattleTest, EndsAsSoonAsHeroDiesEvenMidRound) {
    // T1 還有活著的 Ally（軍隊沒有被殲滅），但英雄死亡就結束
    Role* hero = addHero(10, 0, 0, "0\n0\n");
    Role* ally = addAI(t1, "Ally", 1000, 0, 0);
    Role* s1 = addAI(t2, "S1", 100, 0, 50);
    s1->setDecider(new AIAction(1)); // S1：seed 1 → 普通攻擊；S2 時 seed 2 → 候選 (英雄, Ally) 的 u[2 % 2] = 英雄
    addAI(t2, "S2", 100, 0, 50);
    Battle battle(&t1, &t2);

    Lines out = runBattle(battle);
    EXPECT_EQ(turnHeaders(out), (Lines{
        "輪到 [1]英雄 (HP: 10, MP: 0, STR: 0, State: 正常)。",
        "輪到 [1]Ally (HP: 1000, MP: 0, STR: 0, State: 正常)。",
        "輪到 [2]S1 (HP: 100, MP: 0, STR: 50, State: 正常)。", // S1 打死英雄後，S2 不再行動
    }));
    EXPECT_EQ(out.back(), "[1]英雄 死亡。");
    EXPECT_TRUE(hero->isDead());
    EXPECT_FALSE(ally->isDead());
    EXPECT_FALSE(battle.isHeroAlive());
}

// =====================================================================
// 輪流順序（D1、D20、D30）
// =====================================================================

TEST_F(BattleTest, TroopOneActsBeforeTroopTwoAndDeadRolesAreSkipped) {
    // 第 1 回合英雄打死 S1（行動 + 目標共 2 行）；之後只剩英雄、S2 輪流，英雄再攻擊 4 次打死 S2（350 HP）
    addHero(1000, 0, 100, "0\n0\n0\n0\n0\n0\n");
    addAI(t2, "S1", 100, 0, 0);
    addAI(t2, "S2", 350, 0, 0);
    Battle battle(&t1, &t2);

    Lines out = runBattle(battle);
    EXPECT_EQ(turnHeaders(out), (Lines{
        "輪到 [1]英雄 (HP: 1000, MP: 0, STR: 100, State: 正常)。",
        "輪到 [2]S2 (HP: 350, MP: 0, STR: 0, State: 正常)。",
        "輪到 [1]英雄 (HP: 1000, MP: 0, STR: 100, State: 正常)。",
        "輪到 [2]S2 (HP: 250, MP: 0, STR: 0, State: 正常)。",
        "輪到 [1]英雄 (HP: 1000, MP: 0, STR: 100, State: 正常)。",
        "輪到 [2]S2 (HP: 150, MP: 0, STR: 0, State: 正常)。",
        "輪到 [1]英雄 (HP: 1000, MP: 0, STR: 100, State: 正常)。",
        "輪到 [2]S2 (HP: 50, MP: 0, STR: 0, State: 正常)。",
        "輪到 [1]英雄 (HP: 1000, MP: 0, STR: 100, State: 正常)。",
    }));
    // 只有第 1 回合有 2 位候選要選；之後 Battle 只給活著的角色，只剩 S2 → 自動選、不印提示
    EXPECT_EQ(countLinesStartingWith(out, "選擇 1 位目標:"), 1);
    EXPECT_TRUE(battle.isHeroAlive());
}

TEST_F(BattleTest, SummonedSlimeActsInTheSameRound) {
    addHero(1000, 150, 0, "1\n", {new Summon()});
    addAI(t2, "S1", 50, 0, 0);
    Battle battle(&t1, &t2);

    Lines out = runBattle(battle);
    EXPECT_EQ(turnHeaders(out), (Lines{
        "輪到 [1]英雄 (HP: 1000, MP: 150, STR: 0, State: 正常)。",
        "輪到 [1]Slime (HP: 100, MP: 0, STR: 50, State: 正常)。", // 加入 T1 隊尾，T2 之前就輪到
    }));
    EXPECT_EQ(out.back(), "[2]S1 死亡。");
}

// =====================================================================
// 回合結束：狀態倒數（D11）
// =====================================================================

TEST_F(BattleTest, TimedStatesCountDownAtEndOfEachRound) {
    // 第 1 回合英雄下毒（3 回合，含當前回合）；第 2 回合 MP 不足改普通攻擊
    addHero(1000, 80, 1, "1\n1\n0\n0\n0\n0\n", {new Poison()});
    Role* slime = addAI(t2, "Slime1", 94, 0, 0);
    Battle battle(&t1, &t2);

    Lines out = runBattle(battle);
    Lines slimeTurns;
    for (const std::string& line : turnHeaders(out)) {
        if (line.rfind("輪到 [2]", 0) == 0) slimeTurns.push_back(line);
    }
    EXPECT_EQ(slimeTurns, (Lines{
        "輪到 [2]Slime1 (HP: 94, MP: 0, STR: 0, State: 中毒)。", // 第 1 回合：−30 → 64
        "輪到 [2]Slime1 (HP: 63, MP: 0, STR: 0, State: 中毒)。", // 第 2 回合：−30 → 33
        "輪到 [2]Slime1 (HP: 32, MP: 0, STR: 0, State: 中毒)。", // 第 3 回合：−30 → 2；回合結束換回正常
        "輪到 [2]Slime1 (HP: 1, MP: 0, STR: 0, State: 正常)。",  // 第 4 回合：不再扣血
    }));
    EXPECT_TRUE(slime->isDead()); // 第 5 回合被英雄打死
}

// =====================================================================
// RPG：啟動戰鬥並宣布勝負
// =====================================================================

TEST_F(BattleTest, RPGAnnouncesVictoryWhenHeroSurvives) {
    addHero(500, 0, 100, "0\n");
    addAI(t2, "Slime1", 100, 0, 0);
    RPG rpg;
    OutputCapture capture;
    rpg.GameStart(&t1, &t2);
    rpg.GameEnd();
    Lines out = capture.lines();
    ASSERT_FALSE(out.empty());
    EXPECT_EQ(out.back(), "你獲勝了！");
    EXPECT_EQ(out[out.size() - 2], "[2]Slime1 死亡。");
}

TEST_F(BattleTest, RPGAnnouncesDefeatWhenHeroDies) {
    addHero(10, 0, 0, "0\n");
    addAI(t2, "Slime1", 100, 0, 50);
    RPG rpg;
    OutputCapture capture;
    rpg.GameStart(&t1, &t2);
    rpg.GameEnd();
    Lines out = capture.lines();
    ASSERT_FALSE(out.empty());
    EXPECT_EQ(out.back(), "你失敗了！");
    EXPECT_EQ(out[out.size() - 2], "[1]英雄 死亡。");
}

TEST_F(BattleTest, RPGRejectsMissingTroops) {
    RPG rpg;
    EXPECT_THROW(rpg.GameStart(nullptr, &t2), std::invalid_argument);
    EXPECT_THROW(rpg.GameStart(&t1, nullptr), std::invalid_argument);
}

} // namespace

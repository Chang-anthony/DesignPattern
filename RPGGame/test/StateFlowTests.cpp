/*
 * State 行動流程（State::decision）的單元測試，以及用 testcases/ 整場重播驗證流程。
 *  - 依據：need/need.md「遊戲流程」「角色狀態」「輸出格式」、CLAUDE.md 決策 D5、D8–D12、D16、D17、D29
 *  - 輸出以 rdbuf 導向字串收集（D38）
 *  - TestcaseReplayTest 用「測試用的簡易 Battle 迴圈」驅動（Battle / RPG 尚未實作），等正式的 Battle 完成後改用正式流程
 */
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Role.hpp"
#include "Troop.hpp"
#include "State.hpp"
#include "NormalState.hpp"
#include "PoisonedState.hpp"
#include "PetrochemicaledState.hpp"
#include "CheerupedState.hpp"
#include "IAction.hpp"
#include "AIAction.hpp"
#include "HeroAction.hpp"
#include "Skill.hpp"
#include "BasicAttack.hpp"
#include "Waterball.hpp"
#include "Fireball.hpp"
#include "SelfHealing.hpp"
#include "Petrochemical.hpp"
#include "Poison.hpp"
#include "Summon.hpp"
#include "SelfExplosion.hpp"
#include "Cheerup.hpp"
#include "Curse.hpp"
#include "OnePunch.hpp"
#include "HpHandler.hpp"
#include "PoisonPetrochemicalHandler.hpp"
#include "CheerupHandler.hpp"
#include "NormalHandler.hpp"

namespace {

using Lines = std::vector<std::string>;

class CoutCapture {
public:
    CoutCapture() : old(std::cout.rdbuf(buffer.rdbuf())) {}
    ~CoutCapture() { std::cout.rdbuf(old); }

    Lines lines() const {
        Lines result;
        std::istringstream in(buffer.str());
        std::string line;
        while (std::getline(in, line)) result.push_back(line);
        return result;
    }

private:
    std::ostringstream buffer;
    std::streambuf* old;
};

class StateFlowTest : public ::testing::Test {
protected:
    Troop t1{1};
    Troop t2{2};

    Role* add(Troop& troop, const std::string& name, int hp, int mp, int str,
              const std::vector<Skill*>& skills = {}) {
        Role* role = new Role(hp, mp, str, name, skills);
        troop.addRole(role);
        return role;
    }

    // 讓 role 行動一次（模擬 Battle 輪到它），回傳輸出
    Lines turn(Role* role) {
        int side = role->getTroop() == &t1 ? 1 : 2;
        CoutCapture capture;
        role->takeTurn(t1.getRoles(), t2.getRoles(), side);
        return capture.lines();
    }
};

// =====================================================================
// 「輪到 …」與狀態名稱
// =====================================================================

TEST_F(StateFlowTest, StatesHaveChineseDisplayNames) {
    EXPECT_EQ(NormalState().getDisplayName(), "正常");
    EXPECT_EQ(PetrochemicaledState().getDisplayName(), "石化");
    EXPECT_EQ(PoisonedState().getDisplayName(), "中毒");
    EXPECT_EQ(CheerupedState().getDisplayName(), "受到鼓舞");
    EXPECT_EQ(PoisonedState().getName(), "PoisonedState"); // 類別名稱不變（ExampleTests 依賴它）
}

TEST_F(StateFlowTest, TurnStartsWithHeaderShowingStatsAndState) {
    Role* hero = add(t1, "英雄", 300, 500, 100);
    add(t2, "Slime1", 200, 60, 49);
    AIAction ai;
    hero->setDecider(&ai);

    Lines out = turn(hero);
    ASSERT_FALSE(out.empty());
    EXPECT_EQ(out[0], "輪到 [1]英雄 (HP: 300, MP: 500, STR: 100, State: 正常)。");
}

// =====================================================================
// 預設流程：S1 → S2 → S3（D10、D12）
// =====================================================================

TEST_F(StateFlowTest, NormalFlowPrintsMenuThenActionAndDamage) {
    Role* hero = add(t1, "英雄", 300, 500, 100);
    Role* slime = add(t2, "Slime1", 200, 60, 49, {new Fireball()});
    AIAction ai; // seed 0 → 普通攻擊
    slime->setDecider(&ai);

    EXPECT_EQ(turn(slime), (Lines{
        "輪到 [2]Slime1 (HP: 200, MP: 60, STR: 49, State: 正常)。",
        "選擇行動：(0) 普通攻擊 (1) 火球",
        "[2]Slime1 攻擊 [1]英雄。",
        "[2]Slime1 對 [1]英雄 造成 49 點傷害。",
    }));
    EXPECT_EQ(hero->getHp(), 251);
    EXPECT_EQ(slime->getMp(), 60); // 普通攻擊 MP 0
}

TEST_F(StateFlowTest, ChosenActionCostsMpBeforeExecuting) {
    Role* hero = add(t1, "英雄", 300, 500, 100, {new Fireball(), new Waterball()});
    add(t2, "Slime1", 200, 60, 49);
    add(t2, "Slime2", 200, 200, 50);
    std::istringstream input("1\n");
    HeroAction decider(input);
    hero->setDecider(&decider);

    EXPECT_EQ(turn(hero), (Lines{
        "輪到 [1]英雄 (HP: 300, MP: 500, STR: 100, State: 正常)。",
        "選擇行動：(0) 普通攻擊 (1) 火球 (2) 水球",
        "[1]英雄 對 [2]Slime1, [2]Slime2 使用了 火球。",
        "[1]英雄 對 [2]Slime1 造成 50 點傷害。",
        "[1]英雄 對 [2]Slime2 造成 50 點傷害。",
    }));
    EXPECT_EQ(hero->getMp(), 450);
}

TEST_F(StateFlowTest, InsufficientMpPrintsMessageAndAsksAgain) {
    Role* hero = add(t1, "英雄", 300, 500, 100);
    Role* slime = add(t2, "Slime1", 150, 10, 49, {new Fireball()});
    AIAction ai(1); // seed 1 → 火球（MP 不足）→ seed 2 → 普通攻擊
    slime->setDecider(&ai);

    EXPECT_EQ(turn(slime), (Lines{
        "輪到 [2]Slime1 (HP: 150, MP: 10, STR: 49, State: 正常)。",
        "選擇行動：(0) 普通攻擊 (1) 火球",
        "你缺乏 MP，不能進行此行動。",
        "選擇行動：(0) 普通攻擊 (1) 火球",
        "[2]Slime1 攻擊 [1]英雄。",
        "[2]Slime1 對 [1]英雄 造成 49 點傷害。",
    }));
    EXPECT_EQ(slime->getMp(), 10); // 不合法的行動不扣 MP
    EXPECT_EQ(ai.getSeed(), 3);    // 選了兩次行動；目標只有 1 位 → 自動全選不消耗 seed
    EXPECT_EQ(hero->getHp(), 251);
}

TEST_F(StateFlowTest, HeroIsPromptedForTargetsOnlyWhenChoosing) {
    Role* hero = add(t1, "英雄", 300, 500, 100, {new Waterball()});
    Role* s1 = add(t2, "Slime1", 200, 60, 49);
    Role* s2 = add(t2, "Slime2", 200, 200, 50);
    std::istringstream input("1\n1\n1\n");
    HeroAction decider(input);
    hero->setDecider(&decider);

    EXPECT_EQ(turn(hero), (Lines{
        "輪到 [1]英雄 (HP: 300, MP: 500, STR: 100, State: 正常)。",
        "選擇行動：(0) 普通攻擊 (1) 水球",
        "選擇 1 位目標: (0) [2]Slime1 (1) [2]Slime2",
        "[1]英雄 對 [2]Slime2 使用了 水球。",
        "[1]英雄 對 [2]Slime2 造成 120 點傷害。",
    }));
    EXPECT_EQ(s2->getHp(), 80);

    {
        CoutCapture mute;
        s2->lossHp(80); // Slime2 死亡
    }
    std::vector<Role*> aliveT2{s1};
    CoutCapture capture;
    hero->takeTurn(t1.getRoles(), aliveT2, 1); // 只剩 1 位候選 → 不印「選擇 1 位目標」、不讀行
    EXPECT_EQ(capture.lines(), (Lines{
        "輪到 [1]英雄 (HP: 300, MP: 450, STR: 100, State: 正常)。",
        "選擇行動：(0) 普通攻擊 (1) 水球",
        "[1]英雄 對 [2]Slime1 使用了 水球。",
        "[1]英雄 對 [2]Slime1 造成 120 點傷害。",
    }));
}

TEST_F(StateFlowTest, AIChoosesTargetsWithoutPrompt) {
    add(t1, "A", 500, 0, 0);
    Role* b = add(t1, "B", 500, 0, 0);
    Role* slime = add(t2, "Slime1", 200, 100, 0, {new Waterball()});
    AIAction ai(1); // S1：seed 1 → 水球（seed 變 2）；S2：候選 (A, B)、選 1 位 → u[2 % 2] = A（seed 變 3）
    slime->setDecider(&ai);

    Lines out = turn(slime);
    EXPECT_EQ(out, (Lines{
        "輪到 [2]Slime1 (HP: 200, MP: 100, STR: 0, State: 正常)。",
        "選擇行動：(0) 普通攻擊 (1) 水球",
        "[2]Slime1 對 [1]A 使用了 水球。",
        "[2]Slime1 對 [1]A 造成 120 點傷害。",
    }));
    EXPECT_EQ(b->getHp(), 500);
    EXPECT_EQ(ai.getSeed(), 3);
}

TEST_F(StateFlowTest, RoleWithoutDeciderCannotAct) {
    Role* hero = add(t1, "英雄", 300, 500, 100);
    add(t2, "Slime1", 200, 60, 49);
    CoutCapture mute;
    EXPECT_THROW(hero->takeTurn(t1.getRoles(), t2.getRoles(), 1), std::invalid_argument);
}

// =====================================================================
// 各狀態只覆寫不同的部分（D10、D12）
// =====================================================================

TEST_F(StateFlowTest, PetrifiedRoleOnlyPrintsHeader) {
    Role* hero = add(t1, "英雄", 400, 99999, 30);
    Role* boss = add(t2, "BOSS", 270, 9999, 399);
    AIAction ai;
    boss->setDecider(&ai);
    boss->setState(new PetrochemicaledState());

    EXPECT_EQ(turn(boss), (Lines{"輪到 [2]BOSS (HP: 270, MP: 9999, STR: 399, State: 石化)。"}));
    EXPECT_EQ(ai.getSeed(), 0); // 沒有問決策者
    EXPECT_EQ(hero->getHp(), 400);
}

TEST_F(StateFlowTest, PetrifiedHeroDoesNotConsumeInput) {
    Role* hero = add(t1, "英雄", 400, 99999, 30, {new Waterball()});
    add(t2, "BOSS", 270, 9999, 399);
    std::istringstream input("1\n");
    HeroAction decider(input);
    hero->setDecider(&decider);
    hero->setState(new PetrochemicaledState());

    EXPECT_EQ(turn(hero).size(), 1u);
    CoutCapture mute;
    EXPECT_EQ(decider.chooseAction(hero->getSkills())->getName(), "水球"); // 「1」這行還在
}

TEST_F(StateFlowTest, PoisonedRoleLoses30BeforeActing) {
    Role* hero = add(t1, "英雄", 1000, 500, 0);
    Role* slime = add(t2, "Slime1", 120, 90, 50);
    AIAction ai;
    slime->setDecider(&ai);
    slime->setState(new PoisonedState());

    EXPECT_EQ(turn(slime), (Lines{
        "輪到 [2]Slime1 (HP: 120, MP: 90, STR: 50, State: 中毒)。", // 印的是扣血前的 HP（poison.out）
        "選擇行動：(0) 普通攻擊",
        "[2]Slime1 攻擊 [1]英雄。",
        "[2]Slime1 對 [1]英雄 造成 50 點傷害。",
    }));
    EXPECT_EQ(slime->getHp(), 90);
    EXPECT_EQ(hero->getHp(), 950);
}

TEST_F(StateFlowTest, PoisonedRoleDyingCannotAct) {
    Role* hero = add(t1, "英雄", 1000, 500, 0);
    Role* slime = add(t2, "Slime1", 30, 90, 50);
    AIAction ai;
    slime->setDecider(&ai);
    slime->setState(new PoisonedState());

    EXPECT_EQ(turn(slime), (Lines{
        "輪到 [2]Slime1 (HP: 30, MP: 90, STR: 50, State: 中毒)。",
        "[2]Slime1 死亡。",
    }));
    EXPECT_TRUE(slime->isDead());
    EXPECT_EQ(ai.getSeed(), 0);
    EXPECT_EQ(hero->getHp(), 1000);
}

TEST_F(StateFlowTest, PoisonDeathTriggersObservers) {
    Role* hero = add(t1, "英雄", 300, 500, 0);
    Role* slime = add(t2, "Slime1", 30, 70, 0);
    AIAction ai;
    slime->setDecider(&ai);
    {
        CoutCapture mute;
        Curse().attack(hero, {slime});
    }
    slime->setState(new PoisonedState());
    turn(slime);
    EXPECT_EQ(hero->getHp(), 370); // 詛咒：+ 受詛咒者剩餘 MP（70）
}

TEST_F(StateFlowTest, CheeredRoleUsesDefaultFlowWithBonus) {
    Role* servant = add(t1, "Servant1", 1000, 0, 0);
    Role* slime = add(t2, "Slime1", 500, 0, 0);
    AIAction ai;
    servant->setDecider(&ai);
    servant->setState(new CheerupedState());

    EXPECT_EQ(turn(servant), (Lines{
        "輪到 [1]Servant1 (HP: 1000, MP: 0, STR: 0, State: 受到鼓舞)。",
        "選擇行動：(0) 普通攻擊",
        "[1]Servant1 攻擊 [2]Slime1。",
        "[1]Servant1 對 [2]Slime1 造成 50 點傷害。",
    }));
    EXPECT_EQ(slime->getHp(), 450);
}

// =====================================================================
// 經過流程的特殊技能
// =====================================================================

TEST_F(StateFlowTest, SummonedSlimeActsWithItsOwnAI) {
    Role* hero = add(t1, "英雄", 500, 10000, 30, {new Summon()});
    Role* enemy = add(t2, "Slime1", 1000, 0, 99);
    std::istringstream input("1\n");
    HeroAction decider(input);
    hero->setDecider(&decider);

    EXPECT_EQ(turn(hero), (Lines{
        "輪到 [1]英雄 (HP: 500, MP: 10000, STR: 30, State: 正常)。",
        "選擇行動：(0) 普通攻擊 (1) 召喚",
        "[1]英雄 使用了 召喚。",
    }));
    EXPECT_EQ(hero->getMp(), 9850);
    ASSERT_EQ(t1.getRoles().size(), 2u);

    Role* slime = t1.getRoles()[1];
    EXPECT_EQ(turn(slime), (Lines{ // 史萊姆用 Summon 給的 AIAction（D40）
        "輪到 [1]Slime (HP: 100, MP: 0, STR: 50, State: 正常)。",
        "選擇行動：(0) 普通攻擊",
        "[1]Slime 攻擊 [2]Slime1。",
        "[1]Slime 對 [2]Slime1 造成 50 點傷害。",
    }));
    EXPECT_EQ(enemy->getHp(), 950);
}

TEST_F(StateFlowTest, SelfExplosionThroughFlow) {
    Role* hero = add(t1, "英雄", 500, 200, 0, {new SelfExplosion()});
    Role* a = add(t2, "A", 100, 0, 0);
    Role* b = add(t2, "B", 300, 0, 0);
    std::istringstream input("1\n");
    HeroAction decider(input);
    hero->setDecider(&decider);

    EXPECT_EQ(turn(hero), (Lines{
        "輪到 [1]英雄 (HP: 500, MP: 200, STR: 0, State: 正常)。",
        "選擇行動：(0) 普通攻擊 (1) 自爆",
        "[1]英雄 對 [2]A, [2]B 使用了 自爆。",
        "[1]英雄 對 [2]A 造成 150 點傷害。",
        "[2]A 死亡。",
        "[1]英雄 對 [2]B 造成 150 點傷害。",
        "[1]英雄 死亡。",
    }));
    EXPECT_EQ(hero->getMp(), 0);
    EXPECT_TRUE(a->isDead());
    EXPECT_EQ(b->getHp(), 150);
}

// =====================================================================
// 用 testcases/ 整場重播（測試用的簡易 Battle 迴圈）
// =====================================================================

const std::filesystem::path kTestcaseDir = std::filesystem::path(__FILE__).parent_path().parent_path() / "testcases";

Lines readLines(const std::filesystem::path& path) {
    std::ifstream in(path);
    Lines lines;
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        lines.push_back(line);
    }
    while (!lines.empty() && lines.back().empty()) lines.pop_back();
    return lines;
}

// Client 端的技能建造函式（D26）：測試用版本
Skill* createSkill(const std::string& name) {
    static const std::map<std::string, std::function<Skill*()>> factory = {
        {"水球", [] { return new Waterball(); }},
        {"火球", [] { return new Fireball(); }},
        {"自我治療", [] { return new SelfHealing(); }},
        {"石化", [] { return new Petrochemical(); }},
        {"下毒", [] { return new Poison(); }},
        {"召喚", [] { return new Summon(); }},
        {"自爆", [] { return new SelfExplosion(); }},
        {"鼓舞", [] { return new Cheerup(); }},
        {"詛咒", [] { return new Curse(); }},
        {"一拳攻擊", [] {
             return new OnePunch({new HpHandler(), new PoisonPetrochemicalHandler(), new CheerupHandler(), new NormalHandler()});
         }},
    };
    return factory.at(name)();
}

struct Game {
    Troop t1{1};
    Troop t2{2};
    std::istringstream heroInput;
    std::unique_ptr<HeroAction> heroDecider;
    Role* hero = nullptr;
};

// 解析 .in（D36 的簡化版）：軍隊行建角色、T1 第一位是英雄（D6），其餘行是英雄決策（D37）
void load(Game& game, const Lines& in) {
    Troop* current = nullptr;
    size_t i = 0;
    std::string heroLines;
    for (; i < in.size(); i++) {
        const std::string& line = in[i];
        if (line == "#軍隊-1-開始") { current = &game.t1; continue; }
        if (line == "#軍隊-2-開始") { current = &game.t2; continue; }
        if (line == "#軍隊-1-結束") { current = nullptr; continue; }
        if (line == "#軍隊-2-結束") { i++; break; }
        if (current == nullptr) continue;
        std::istringstream ss(line);
        std::string name, skillName;
        int hp, mp, str;
        ss >> name >> hp >> mp >> str;
        Role* role = new Role(hp, mp, str, name);
        while (ss >> skillName) role->addSkill(createSkill(skillName));
        current->addRole(role);
        if (game.hero == nullptr) {
            game.hero = role;
            role->setIdentity('h');
        } else {
            role->setDecider(new AIAction());
        }
    }
    for (; i < in.size(); i++) heroLines += in[i] + "\n";
    game.heroInput.str(heroLines);
    game.heroDecider = std::make_unique<HeroAction>(game.heroInput);
    game.hero->setDecider(game.heroDecider.get());
}

std::vector<Role*> alive(const Troop& troop) {
    std::vector<Role*> result;
    for (Role* role : troop.getRoles()) {
        if (!role->isDead()) result.push_back(role);
    }
    return result;
}

// 測試用的 Battle 迴圈（D1、D11、D20、D30）：T1 → T2、每圈重讀人數、跳過死者、每次行動後檢查結束、回合結束倒數
Lines play(Game& game) {
    CoutCapture capture;
    auto ended = [&] { return game.hero->isDead() || game.t1.Annihilated() || game.t2.Annihilated(); };
    for (int round = 0; round < 1000 && !ended(); round++) {
        for (int side = 1; side <= 2 && !ended(); side++) {
            Troop& troop = side == 1 ? game.t1 : game.t2;
            for (size_t idx = 0; idx < troop.getRoles().size() && !ended(); idx++) {
                Role* role = troop.getRoles()[idx];
                if (role->isDead()) continue;
                role->takeTurn(alive(game.t1), alive(game.t2), side);
            }
        }
        for (Role* role : game.t1.getRoles()) role->endThisRound();
        for (Role* role : game.t2.getRoles()) role->endThisRound();
    }
    std::cout << (game.hero->isDead() ? "你失敗了！" : "你獲勝了！") << std::endl;
    return capture.lines();
}

class TestcaseReplayTest : public ::testing::TestWithParam<std::string> {};

TEST_P(TestcaseReplayTest, OutputMatchesExpectedFile) {
    const std::string name = GetParam();
    Lines in = readLines(kTestcaseDir / (name + ".in"));
    Lines expected = readLines(kTestcaseDir / (name + ".out"));
    ASSERT_FALSE(in.empty()) << "找不到 " << (kTestcaseDir / (name + ".in")).string();
    ASSERT_FALSE(expected.empty());

    Game game;
    load(game, in);
    Lines actual = play(game);

    size_t n = std::min(actual.size(), expected.size());
    for (size_t i = 0; i < n; i++) {
        ASSERT_EQ(actual[i], expected[i]) << name << ".out 第 " << (i + 1) << " 行不同";
    }
    EXPECT_EQ(actual.size(), expected.size()) << "行數不同";
}

INSTANTIATE_TEST_SUITE_P(AllTestcases, TestcaseReplayTest,
                         ::testing::Values("cheerup", "curse", "one-punch", "only-basic-attack", "petrochemical",
                                           "poison", "self-explosion", "self-healing", "summon",
                                           "waterball-and-fireball-1v2"),
                         [](const ::testing::TestParamInfo<std::string>& info) {
                             std::string s = info.param;
                             for (char& ch : s) if (ch == '-') ch = '_';
                             return s;
                         });

} // namespace

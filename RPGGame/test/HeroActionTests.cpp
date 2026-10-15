/*
 * HeroAction 的單元測試。
 *  - 依據：need/need.md「輸入格式」（英雄決策一行一個、以「, 」隔開；S1 與 S2 共用同一串輸入）、
 *          CLAUDE.md 決策 D4、D5、D8、D37
 *  - 輸入用 std::istringstream 模擬（D37：HeroAction 注入 std::istream&）
 */
#include <gtest/gtest.h>

#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Output.hpp"
#include "HeroAction.hpp"
#include "IAction.hpp"
#include "Role.hpp"
#include "Skill.hpp"
#include "BasicAttack.hpp"
#include "Fireball.hpp"
#include "Waterball.hpp"
#include "Cheerup.hpp"

using Names = std::vector<std::string>;

namespace {

// 在作用域內把模組輸出（io::output()）導向字串，解構時還原（D50）
class OutputCapture {
public:
    OutputCapture() : sink(buffer), previous(io::setOutput(&sink)) {}
    ~OutputCapture() { io::setOutput(previous); }

    std::vector<std::string> lines() const {
        std::vector<std::string> result;
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

Names namesOf(const std::vector<Role*>& roles) {
    Names names;
    for (Role* role : roles) names.push_back(role->getName());
    return names;
}

} // namespace

class HeroActionTest : public ::testing::Test {
protected:
    OutputCapture mute; // chooseTargets 會印「選擇 m 位目標」，其他測試不檢查輸出
    Role a{100, 0, 0, "A"};
    Role b{100, 0, 0, "B"};
    Role c{100, 0, 0, "C"};
    std::vector<Role*> abc{&a, &b, &c};
    Role hero{300, 500, 100, "英雄", {new Fireball(), new Waterball()}}; // (0) 普通攻擊 (1) 火球 (2) 水球
};

// =====================================================================
// S1：選行動
// =====================================================================

TEST_F(HeroActionTest, ChooseActionReadsIndexFromNextLine) {
    std::istringstream input("2\n");
    HeroAction decider(input);
    EXPECT_EQ(decider.chooseAction(hero.getSkills())->getName(), "水球");
}

TEST_F(HeroActionTest, EachChooseActionConsumesOneLine) {
    std::istringstream input("1\n0\n2\n");
    HeroAction decider(input);
    Names picked;
    for (int i = 0; i < 3; i++) picked.push_back(decider.chooseAction(hero.getSkills())->getName());
    EXPECT_EQ(picked, (Names{"火球", "普通攻擊", "水球"}));
}

TEST_F(HeroActionTest, InsufficientMpRetryReadsNextLine) {
    // 需求：MP 不足時英雄被要求再次決策，也就是讀下一行 <英雄決策-i+1>
    Role poorHero(100, 30, 10, "英雄", {new Fireball()}); // 火球需要 50 MP
    std::istringstream input("1\n0\n");
    HeroAction decider(input);

    Names log;
    Skill* skill = decider.chooseAction(poorHero.getSkills());
    while (!poorHero.checkMp(skill)) {
        log.push_back("MP 不足：" + skill->getName());
        skill = decider.chooseAction(poorHero.getSkills());
    }
    log.push_back(skill->getName());
    EXPECT_EQ(log, (Names{"MP 不足：火球", "普通攻擊"}));
}

// =====================================================================
// S2：選目標
// =====================================================================

TEST_F(HeroActionTest, ChooseTargetsReturnsCandidatesInInputOrder) {
    std::istringstream input("2, 0\n");
    HeroAction decider(input);
    EXPECT_EQ(namesOf(decider.chooseTargets(abc, 2)), (Names{"C", "A"}));
}

TEST_F(HeroActionTest, ChooseSingleTarget) {
    std::istringstream input("1\n");
    HeroAction decider(input);
    EXPECT_EQ(namesOf(decider.chooseTargets(abc, 1)), (Names{"B"}));
}

TEST_F(HeroActionTest, AutoSelectionDoesNotConsumeInput) {
    // m = 0 或 n ≤ m 時略過 S2（D8），不能吃掉下一個決策行
    std::istringstream input("2\n");
    HeroAction decider(input);
    EXPECT_EQ(namesOf(decider.chooseTargets(abc, 3)), (Names{"A", "B", "C"}));      // n = m
    EXPECT_EQ(namesOf(decider.chooseTargets({&a}, 1)), (Names{"A"}));               // n = m = 1
    EXPECT_EQ(namesOf(decider.chooseTargets({&a, &b}, 3)), (Names{"A", "B"}));      // n < m
    EXPECT_TRUE(decider.chooseTargets({}, 0).empty());                              // m = 0（召喚、自我治療）
    EXPECT_EQ(decider.chooseAction(hero.getSkills())->getName(), "水球");          // "2" 仍是下一個決策
}

TEST_F(HeroActionTest, PromptsForTargetsOnlyWhenActuallyChoosing) {
    // 需求「輸出格式」：S2 時印「選擇 <m> 位目標: (0) <候選-1> (1) <候選-2> …」（§7.2 I7）
    std::istringstream input("2, 0\n");
    HeroAction decider(input);
    OutputCapture capture;
    decider.chooseTargets(abc, 2);
    decider.chooseTargets({&a, &b}, 2); // n = m：略過 S2，不印
    decider.chooseTargets({}, 0);       // m = 0：不印
    EXPECT_EQ(capture.lines(), (Names{"選擇 2 位目標: (0) A (1) B (2) C"}));
}

// =====================================================================
// 輸入格式的容錯
// =====================================================================

TEST_F(HeroActionTest, AcceptsWindowsLineEndings) {
    std::istringstream input("1\r\n2, 0\r\n");
    HeroAction decider(input);
    EXPECT_EQ(decider.chooseAction(hero.getSkills())->getName(), "火球");
    EXPECT_EQ(namesOf(decider.chooseTargets(abc, 2)), (Names{"C", "A"}));
}

TEST_F(HeroActionTest, SkipsBlankLines) {
    std::istringstream input("\n   \n1\n\n2, 0\n");
    HeroAction decider(input);
    EXPECT_EQ(decider.chooseAction(hero.getSkills())->getName(), "火球");
    EXPECT_EQ(namesOf(decider.chooseTargets(abc, 2)), (Names{"C", "A"}));
}

TEST_F(HeroActionTest, ThrowsWhenInputRunsOut) {
    std::istringstream input("1\n");
    HeroAction decider(input);
    decider.chooseAction(hero.getSkills());
    EXPECT_THROW(decider.chooseAction(hero.getSkills()), std::runtime_error);
}

TEST_F(HeroActionTest, ThrowsOnOutOfRangeIndex) {
    std::istringstream input("3\n0, 5\n");
    HeroAction decider(input);
    EXPECT_THROW(decider.chooseAction(hero.getSkills()), std::out_of_range); // 只有 0–2
    EXPECT_THROW(decider.chooseTargets(abc, 2), std::out_of_range);          // 只有 0–2
}

TEST_F(HeroActionTest, ThrowsWhenTargetCountDiffersFromM) {
    std::istringstream input("0\n");
    HeroAction decider(input);
    EXPECT_THROW(decider.chooseTargets(abc, 2), std::invalid_argument);
}

// =====================================================================
// 與 Role 搭配（D4、D6）
// =====================================================================

TEST_F(HeroActionTest, RoleCarriesHeroActionThroughIActionInterface) {
    std::istringstream input("2\n");
    hero.setIdentity('h');
    hero.setDecider(new HeroAction(input)); // Role 擁有決策者（D49）

    EXPECT_TRUE(hero.isHero());
    EXPECT_EQ(hero.getDecider()->chooseAction(hero.getSkills())->getName(), "水球");
}

// =====================================================================
// 重現測資中英雄的決策
// =====================================================================

// testcases/waterball-and-fireball-1v2.in 的英雄決策：1 / 2 / 1 / 2 / 1 / 2 / 1
//   第 1 回合 火球（2 位敵軍全選，不讀行）
//   第 2、3 回合 水球 → 選 (1) Slime2
//   第 4 回合 Slime2 已死，水球只剩 Slime1 → 自動選，不讀行
//   第 5 回合 火球（只剩 Slime1，不讀行）
TEST_F(HeroActionTest, ReplaysHeroFromWaterballAndFireballTestcase) {
    std::istringstream input("1\n2\n1\n2\n1\n2\n1\n");
    HeroAction decider(input);
    Role slime1(200, 60, 49, "Slime1");
    Role slime2(200, 200, 50, "Slime2");

    Names log;
    auto takeTurn = [&](const std::vector<Role*>& enemies) {
        Skill* skill = decider.chooseAction(hero.getSkills());
        Candidates candidates = skill->getCandidates(&hero, {&hero}, enemies, 1);
        Names targets = namesOf(decider.chooseTargets(candidates.roles, candidates.m));
        std::string line = skill->getName() + " →";
        for (const std::string& name : targets) line += " " + name;
        log.push_back(line);
    };

    takeTurn({&slime1, &slime2});
    takeTurn({&slime1, &slime2});
    takeTurn({&slime1, &slime2});
    takeTurn({&slime1});
    takeTurn({&slime1});

    EXPECT_EQ(log, (Names{
        "火球 → Slime1 Slime2",
        "水球 → Slime2",
        "水球 → Slime2",
        "水球 → Slime1",
        "火球 → Slime1",
    }));
    EXPECT_THROW(decider.chooseAction(hero.getSkills()), std::runtime_error); // 7 行剛好用完
}

// testcases/cheerup.in 的英雄決策：1 / 0, 1, 2 / 1 / 2, 3, 4 / 0
//   鼓舞要從 5 位友軍選 3 位 → 讀一行 3 個數字
TEST_F(HeroActionTest, ReplaysHeroFromCheerupTestcase) {
    std::istringstream input("1\n0, 1, 2\n1\n2, 3, 4\n0\n");
    HeroAction decider(input);
    Role cheerHero(500, 10000, 30, "英雄", {new Cheerup()});
    std::vector<Role*> t1{&cheerHero};
    std::vector<std::unique_ptr<Role>> servants;
    for (int i = 1; i <= 5; i++) {
        servants.push_back(std::make_unique<Role>(1000, 0, 0, "Servant" + std::to_string(i)));
        t1.push_back(servants.back().get());
    }
    Role slime1(500, 0, 0, "Slime1");
    std::vector<Role*> t2{&slime1};

    auto turn = [&]() {
        Skill* skill = decider.chooseAction(cheerHero.getSkills());
        Candidates candidates = skill->getCandidates(&cheerHero, t1, t2, 1);
        Names line{skill->getName()};
        for (const std::string& name : namesOf(decider.chooseTargets(candidates.roles, candidates.m))) line.push_back(name);
        return line;
    };

    EXPECT_EQ(turn(), (Names{"鼓舞", "Servant1", "Servant2", "Servant3"}));
    EXPECT_EQ(turn(), (Names{"鼓舞", "Servant3", "Servant4", "Servant5"}));
    EXPECT_EQ(turn(), (Names{"普通攻擊", "Slime1"}));
}

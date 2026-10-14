/*
 * IAction / AIAction 的單元測試。
 *  - 依據：need/need.md「AI 決策」章節、CLAUDE.md 決策 D4、D5、D7、D8
 *  - seed 規則：每做完一個決策 seed + 1；S2 自動全選（m = 0 或 n ≤ m）不算決策
 */
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "AIAction.hpp"
#include "IAction.hpp"
#include "Role.hpp"
#include "Skill.hpp"
#include "BasicAttack.hpp"
#include "Fireball.hpp"
#include "Waterball.hpp"
#include "Curse.hpp"
#include "Poison.hpp"

using Names = std::vector<std::string>;

namespace {

Names namesOf(const std::vector<Role*>& roles) {
    Names names;
    for (Role* role : roles) names.push_back(role->getName());
    return names;
}

} // namespace

class AIActionTest : public ::testing::Test {
protected:
    Role a{100, 0, 0, "A"};
    Role b{100, 0, 0, "B"};
    Role c{100, 0, 0, "C"};
    std::vector<Role*> abc{&a, &b, &c};
};

// =====================================================================
// S1：選行動
// =====================================================================

TEST_F(AIActionTest, SeedStartsAtZero) {
    AIAction ai;
    EXPECT_EQ(ai.getSeed(), 0);
}

TEST_F(AIActionTest, ChooseActionPicksSeedModuloActionCountAndIncrementsSeed) {
    Role role(100, 500, 10, "AI", {new Fireball(), new Waterball(), new Curse()}); // 4 個行動
    const std::vector<Skill*>& skills = role.getSkills();
    AIAction ai;

    Names picked;
    for (int i = 0; i < 6; i++) picked.push_back(ai.chooseAction(skills)->getName());

    EXPECT_EQ(picked, (Names{"普通攻擊", "火球", "水球", "詛咒", "普通攻擊", "火球"}));
    EXPECT_EQ(ai.getSeed(), 6);
}

TEST_F(AIActionTest, ChooseActionStartsFromGivenSeed) {
    Role role(100, 500, 10, "AI", {new Fireball(), new Waterball()}); // 3 個行動
    AIAction ai(5);
    EXPECT_EQ(ai.chooseAction(role.getSkills())->getName(), "水球"); // 5 % 3 = 2
    EXPECT_EQ(ai.getSeed(), 6);
}

TEST_F(AIActionTest, ChooseActionWithNoActionThrows) {
    AIAction ai;
    EXPECT_THROW(ai.chooseAction({}), std::invalid_argument);
    EXPECT_EQ(ai.getSeed(), 0);
}

// =====================================================================
// S2：選目標
// =====================================================================

TEST_F(AIActionTest, ChooseTargetsMatchesRequirementExample) {
    // 需求範例：seed = 2、候選 (A, B, C)、選 2 位 → (C, A)，選完 seed = 3
    AIAction ai(2);
    EXPECT_EQ(namesOf(ai.chooseTargets(abc, 2)), (Names{"C", "A"}));
    EXPECT_EQ(ai.getSeed(), 3);
}

TEST_F(AIActionTest, ChooseSingleTargetRotatesWithSeed) {
    AIAction ai;
    EXPECT_EQ(namesOf(ai.chooseTargets(abc, 1)), (Names{"A"}));
    EXPECT_EQ(namesOf(ai.chooseTargets(abc, 1)), (Names{"B"}));
    EXPECT_EQ(namesOf(ai.chooseTargets(abc, 1)), (Names{"C"}));
    EXPECT_EQ(namesOf(ai.chooseTargets(abc, 1)), (Names{"A"}));
    EXPECT_EQ(ai.getSeed(), 4);
}

TEST_F(AIActionTest, SelectingManyTargetsIncrementsSeedOnlyOnce) {
    Role d(100, 0, 0, "D");
    std::vector<Role*> abcd{&a, &b, &c, &d};
    AIAction ai(1);
    EXPECT_EQ(namesOf(ai.chooseTargets(abcd, 3)), (Names{"B", "C", "D"}));
    EXPECT_EQ(ai.getSeed(), 2);
    EXPECT_EQ(namesOf(ai.chooseTargets(abcd, 3)), (Names{"C", "D", "A"})); // 繞回開頭
    EXPECT_EQ(ai.getSeed(), 3);
}

TEST_F(AIActionTest, CandidatesNotMoreThanMAreAllSelectedWithoutUsingSeed) {
    AIAction ai(7);
    EXPECT_EQ(namesOf(ai.chooseTargets(abc, 3)), (Names{"A", "B", "C"})); // n = m
    EXPECT_EQ(namesOf(ai.chooseTargets({&b}, 1)), (Names{"B"}));         // n = m = 1
    EXPECT_EQ(namesOf(ai.chooseTargets({&a, &b}, 3)), (Names{"A", "B"})); // n < m（鼓舞只剩 2 位友軍）
    EXPECT_EQ(ai.getSeed(), 7); // 略過 S2，不是 AI 做的決策
}

TEST_F(AIActionTest, NoTargetSkillSkipsSelectionWithoutUsingSeed) {
    AIAction ai(4);
    EXPECT_TRUE(ai.chooseTargets({}, 0).empty()); // 召喚、自我治療：m = 0
    EXPECT_EQ(ai.getSeed(), 4);
}

// =====================================================================
// 與 Role 搭配（D4、D5）
// =====================================================================

TEST_F(AIActionTest, RoleUsesAIActionThroughIActionInterface) {
    Role role(100, 0, 10, "Slime", {new Poison()});
    AIAction ai;
    role.setDecider(&ai);

    IAction* decider = role.getDecider();
    EXPECT_NE(dynamic_cast<BasicAttack*>(decider->chooseAction(role.getSkills())), nullptr);
    EXPECT_EQ(decider->chooseAction(role.getSkills())->getName(), "下毒");
}

// 重現 testcases/waterball-and-fireball-1v2 中 [2]Slime1 的四次輪到（行動：普通攻擊、火球；MP 60）：
//   回合 1 普通攻擊、回合 2 火球、回合 3 普通攻擊、回合 4 火球 MP 不足 → 重選 → 普通攻擊
// 敵軍只有英雄 1 位，S2 都是自動全選；若自動全選也讓 seed + 1，回合 2 就會選到普通攻擊而對不上測資
TEST_F(AIActionTest, ReplaysSlime1FromWaterballAndFireballTestcase) {
    Role hero(300, 500, 100, "英雄");
    Role slime1(200, 60, 49, "Slime1", {new Fireball()});
    AIAction ai;

    Names log;
    auto takeTurn = [&]() {
        Skill* skill = ai.chooseAction(slime1.getSkills());
        while (!slime1.checkMp(skill)) {
            log.push_back("MP 不足：" + skill->getName());
            skill = ai.chooseAction(slime1.getSkills());
        }
        Candidates candidates = skill->getCandidates(&slime1, {&hero}, {&slime1}, 2);
        EXPECT_EQ(ai.chooseTargets(candidates.roles, candidates.m), (std::vector<Role*>{&hero}));
        slime1.lossMp(skill->getMp());
        log.push_back(skill->getName());
    };

    for (int round = 0; round < 4; round++) takeTurn();

    EXPECT_EQ(log, (Names{"普通攻擊", "火球", "普通攻擊", "MP 不足：火球", "普通攻擊"}));
    EXPECT_EQ(slime1.getMp(), 10);
    EXPECT_EQ(ai.getSeed(), 5);
}

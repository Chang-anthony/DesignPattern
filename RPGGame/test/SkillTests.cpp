/*
 * 技能（行動）的單元測試。
 *  - 依據：need/need.txt、CLAUDE.md 決策 D1–D39、testcases/*.out 的輸出格式
 *  - 輸出以 rdbuf 導向字串收集（D38）
 */
#include <gtest/gtest.h>

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

#include "OnePunchHandler.hpp"
#include "HpHandler.hpp"
#include "PoisonPetrochemicalHandler.hpp"
#include "CheerupHandler.hpp"
#include "NormalHandler.hpp"

#include "Role.hpp"
#include "Troop.hpp"
#include "State.hpp"
#include "NormalState.hpp"
#include "PoisonedState.hpp"
#include "PetrochemicaledState.hpp"
#include "CheerupedState.hpp"
#include "SkillObserver.hpp"
#include "SummonObserver.hpp"
#include "AIAction.hpp"
#include "CurserObserver.hpp"

namespace {

// ===== 測試輔助 =====

// 在作用域內把 std::cout 導向字串（D38）
class CoutCapture {
public:
    CoutCapture() : old(std::cout.rdbuf(buffer.rdbuf())) {}
    ~CoutCapture() { std::cout.rdbuf(old); }

    std::vector<std::string> lines() const {
        std::vector<std::string> result;
        std::istringstream in(buffer.str());
        std::string line;
        while (std::getline(in, line)) {
            result.push_back(line);
        }
        return result;
    }

private:
    std::ostringstream buffer;
    std::streambuf* old;
};

// Client 端組裝一拳攻擊的處理鏈（D21、D23）：順序 = 需求列出的由上而下
std::vector<OnePunchHandler*> requirementChain() {
    return {new HpHandler(), new PoisonPetrochemicalHandler(), new CheerupHandler(), new NormalHandler()};
}

using Lines = std::vector<std::string>;

class SkillBehaviorTest : public ::testing::Test {
protected:
    Troop t1{1};
    Troop t2{2};

    Role* add(Troop& troop, const std::string& name, int hp, int mp, int str) {
        Role* role = new Role(hp, mp, str, name);
        troop.addRole(role);
        return role;
    }

    // 模擬 Battle 給的名單：依隊伍順序（D30、D31）
    std::vector<Role*> alive1() const { return t1.getRoles(); }
    std::vector<Role*> alive2() const { return t2.getRoles(); }

    // 執行技能並回傳輸出
    Lines run(Skill& skill, Role* actor, const std::vector<Role*>& targets) {
        CoutCapture capture;
        skill.attack(actor, targets);
        return capture.lines();
    }
};

// =====================================================================
// 名稱與 MP（D27：每個技能各自持有中文名稱）
// =====================================================================

TEST_F(SkillBehaviorTest, EachActionHasItsChineseNameAndMpCost) {
    struct Expect {
        std::function<Skill*()> make;
        std::string name;
        int mp;
    };
    std::vector<Expect> expects = {
        {[] { return new BasicAttack(); }, "普通攻擊", 0},
        {[] { return new Waterball(); }, "水球", 50},
        {[] { return new Fireball(); }, "火球", 50},
        {[] { return new SelfHealing(); }, "自我治療", 50},
        {[] { return new Petrochemical(); }, "石化", 100},
        {[] { return new Poison(); }, "下毒", 80},
        {[] { return new Summon(); }, "召喚", 150},
        {[] { return new SelfExplosion(); }, "自爆", 200},
        {[] { return new Cheerup(); }, "鼓舞", 100},
        {[] { return new Curse(); }, "詛咒", 100},
        {[] { return new OnePunch(requirementChain()); }, "一拳攻擊", 180},
    };
    for (const Expect& e : expects) {
        Skill* skill = e.make();
        SCOPED_TRACE(e.name);
        EXPECT_EQ(skill->getName(), e.name);
        EXPECT_EQ(skill->getMp(), e.mp);
        delete skill;
    }
}

// =====================================================================
// Role 自帶普通攻擊（D28）
// =====================================================================

TEST_F(SkillBehaviorTest, RoleAlwaysHasBasicAttackAsFirstAction) {
    Role role(100, 100, 10, "A");
    ASSERT_EQ(role.getSkills().size(), 1u);
    EXPECT_NE(dynamic_cast<BasicAttack*>(role.getSkills()[0]), nullptr);

    role.addSkill(new Fireball());
    role.addSkill(new Waterball());
    ASSERT_EQ(role.getSkills().size(), 3u);
    EXPECT_EQ(role.getSkills()[0]->getName(), "普通攻擊");
    EXPECT_EQ(role.getSkills()[1]->getName(), "火球");
    EXPECT_EQ(role.getSkills()[2]->getName(), "水球");

    Role withSkills(100, 100, 10, "B", {new Curse(), new Summon()});
    ASSERT_EQ(withSkills.getSkills().size(), 3u);
    EXPECT_EQ(withSkills.getSkills()[0]->getName(), "普通攻擊");
    EXPECT_EQ(withSkills.getSkills()[1]->getName(), "詛咒");
    EXPECT_EQ(withSkills.getSkills()[2]->getName(), "召喚");
}

TEST_F(SkillBehaviorTest, DisplayNameHasTroopPrefix) {
    Role* hero = add(t1, "英雄", 100, 0, 0);
    Role* slime = add(t2, "Slime1", 100, 0, 0);
    Role alone(1, 0, 0, "Alone");
    EXPECT_EQ(hero->getDisplayName(), "[1]英雄");
    EXPECT_EQ(slime->getDisplayName(), "[2]Slime1");
    EXPECT_EQ(alone.getDisplayName(), "Alone");
}

// =====================================================================
// 候選名單（D29–D34）
// =====================================================================

TEST_F(SkillBehaviorTest, DefaultCandidatesAreOneEnemy) {
    Role* hero = add(t1, "英雄", 100, 0, 0);
    Role* ally = add(t1, "Ally", 100, 0, 0);
    Role* s1 = add(t2, "S1", 100, 0, 0);
    Role* s2 = add(t2, "S2", 100, 0, 0);

    std::vector<Skill*> oneEnemySkills = {new BasicAttack(), new Waterball(), new Petrochemical(),
                                          new Poison(), new Curse(), new OnePunch({})};
    for (Skill* skill : oneEnemySkills) {
        SCOPED_TRACE(skill->getName());
        Candidates fromT1 = skill->getCandidates(hero, alive1(), alive2(), 1);
        EXPECT_EQ(fromT1.roles, (std::vector<Role*>{s1, s2}));
        EXPECT_EQ(fromT1.m, 1);

        Candidates fromT2 = skill->getCandidates(s1, alive1(), alive2(), 2);
        EXPECT_EQ(fromT2.roles, (std::vector<Role*>{hero, ally}));
        EXPECT_EQ(fromT2.m, 1);
        delete skill;
    }
}

TEST_F(SkillBehaviorTest, FireballCandidatesAreAllEnemies) {
    Role* hero = add(t1, "英雄", 100, 0, 0);
    Role* s1 = add(t2, "S1", 100, 0, 0);
    Role* s2 = add(t2, "S2", 100, 0, 0);
    Role* s3 = add(t2, "S3", 100, 0, 0);

    Fireball fireball;
    Candidates c = fireball.getCandidates(hero, alive1(), alive2(), 1);
    EXPECT_EQ(c.roles, (std::vector<Role*>{s1, s2, s3}));
    EXPECT_EQ(c.m, 3); // m = n → 自動全選
}

TEST_F(SkillBehaviorTest, SelfHealingCandidateIsSelf) {
    Role* hero = add(t1, "英雄", 100, 0, 0);
    add(t1, "Ally", 100, 0, 0);
    add(t2, "S1", 100, 0, 0);

    SelfHealing healing;
    Candidates c = healing.getCandidates(hero, alive1(), alive2(), 1);
    EXPECT_EQ(c.roles, (std::vector<Role*>{hero}));
    EXPECT_EQ(c.m, 1);
}

TEST_F(SkillBehaviorTest, SummonHasNoCandidates) {
    Role* hero = add(t1, "英雄", 100, 0, 0);
    add(t2, "S1", 100, 0, 0);

    Summon summon;
    Candidates c = summon.getCandidates(hero, alive1(), alive2(), 1);
    EXPECT_TRUE(c.roles.empty());
    EXPECT_EQ(c.m, 0);
}

TEST_F(SkillBehaviorTest, CheerupCandidatesAreAlliesExcludingSelfAndPickThree) {
    Role* a = add(t1, "A", 100, 0, 0);
    Role* b = add(t1, "B", 100, 0, 0);
    Role* c = add(t1, "C", 100, 0, 0);
    Role* d = add(t1, "D", 100, 0, 0);
    Role* e = add(t2, "E", 100, 0, 0);
    Role* f = add(t2, "F", 100, 0, 0);

    Cheerup cheerup;
    Candidates fromB = cheerup.getCandidates(b, alive1(), alive2(), 1);
    EXPECT_EQ(fromB.roles, (std::vector<Role*>{a, c, d}));
    EXPECT_EQ(fromB.m, 3);

    Candidates fromE = cheerup.getCandidates(e, alive1(), alive2(), 2);
    EXPECT_EQ(fromE.roles, (std::vector<Role*>{f}));
    EXPECT_EQ(fromE.m, 3); // n ≤ m → 由 IAction 自動全選（D8）
}

TEST_F(SkillBehaviorTest, SelfExplosionCandidatesAreEveryoneElseInT1ThenT2Order) {
    Role* a = add(t1, "A", 100, 0, 0);
    Role* b = add(t1, "B", 100, 0, 0);
    Role* c = add(t2, "C", 100, 0, 0);
    Role* d = add(t2, "D", 100, 0, 0);

    SelfExplosion explosion;
    // T2 的角色施放時，順序仍為 T1 → T2（D31、D34）
    Candidates fromC = explosion.getCandidates(c, alive1(), alive2(), 2);
    EXPECT_EQ(fromC.roles, (std::vector<Role*>{a, b, d}));
    EXPECT_EQ(fromC.m, 3);

    Candidates fromA = explosion.getCandidates(a, alive1(), alive2(), 1);
    EXPECT_EQ(fromA.roles, (std::vector<Role*>{b, c, d}));
}

// =====================================================================
// 行動訊息（S3）
// =====================================================================

TEST_F(SkillBehaviorTest, AnnounceFormats) {
    Role* hero = add(t1, "英雄", 100, 500, 30);
    Role* s1 = add(t2, "Slime1", 100, 0, 0);
    Role* s2 = add(t2, "Slime2", 100, 0, 0);

    CoutCapture capture;
    BasicAttack().announce(hero, {s1});
    Fireball().announce(hero, {s1, s2});
    Waterball().announce(hero, {s2});
    SelfHealing().announce(s1, {s1});
    Summon().announce(hero, {});
    EXPECT_EQ(capture.lines(), (Lines{
        "[1]英雄 攻擊 [2]Slime1。",
        "[1]英雄 對 [2]Slime1, [2]Slime2 使用了 火球。",
        "[1]英雄 對 [2]Slime2 使用了 水球。",
        "[2]Slime1 使用了 自我治療。",
        "[1]英雄 使用了 召喚。",
    }));
}

// =====================================================================
// 傷害類技能（D16、D17）
// =====================================================================

TEST_F(SkillBehaviorTest, BasicAttackDealsStrDamage) {
    Role* hero = add(t1, "英雄", 500, 500, 40);
    Role* slime = add(t2, "Slime1", 100, 100, 30);

    BasicAttack attack;
    EXPECT_EQ(run(attack, hero, {slime}), (Lines{"[1]英雄 對 [2]Slime1 造成 40 點傷害。"}));
    EXPECT_EQ(slime->getHp(), 60);
    EXPECT_EQ(hero->getMp(), 500); // 技能本身不扣 MP（S3 由 State 流程扣，D9）
}

TEST_F(SkillBehaviorTest, BasicAttackWithZeroStrStillPrintsZeroDamage) {
    Role* servant = add(t1, "Servant4", 1000, 0, 0);
    Role* slime = add(t2, "Slime1", 500, 0, 0);

    BasicAttack attack;
    EXPECT_EQ(run(attack, servant, {slime}), (Lines{"[1]Servant4 對 [2]Slime1 造成 0 點傷害。"}));
    EXPECT_EQ(slime->getHp(), 500);
}

TEST_F(SkillBehaviorTest, WaterballDeals120Damage) {
    Role* hero = add(t1, "英雄", 300, 500, 100);
    Role* slime = add(t2, "Slime2", 150, 200, 50);

    Waterball waterball;
    EXPECT_EQ(run(waterball, hero, {slime}), (Lines{"[1]英雄 對 [2]Slime2 造成 120 點傷害。"}));
    EXPECT_EQ(slime->getHp(), 30);
}

TEST_F(SkillBehaviorTest, FireballDeals50ToEachTargetInOrder) {
    Role* hero = add(t1, "英雄", 300, 500, 100);
    Role* s1 = add(t2, "Slime1", 200, 60, 49);
    Role* s2 = add(t2, "Slime2", 200, 200, 50);

    Fireball fireball;
    EXPECT_EQ(run(fireball, hero, {s1, s2}), (Lines{
        "[1]英雄 對 [2]Slime1 造成 50 點傷害。",
        "[1]英雄 對 [2]Slime2 造成 50 點傷害。",
    }));
    EXPECT_EQ(s1->getHp(), 150);
    EXPECT_EQ(s2->getHp(), 150);
}

TEST_F(SkillBehaviorTest, DeathMessageFollowsEachTargetsDamageImmediately) {
    Role* hero = add(t1, "英雄", 300, 500, 100);
    Role* s1 = add(t2, "Slime1", 50, 0, 0);
    Role* s2 = add(t2, "Slime2", 30, 0, 0);

    Fireball fireball;
    EXPECT_EQ(run(fireball, hero, {s1, s2}), (Lines{
        "[1]英雄 對 [2]Slime1 造成 50 點傷害。",
        "[2]Slime1 死亡。",
        "[1]英雄 對 [2]Slime2 造成 50 點傷害。",
        "[2]Slime2 死亡。",
    }));
    EXPECT_TRUE(s1->isDead());
    EXPECT_TRUE(s2->isDead());
}

TEST_F(SkillBehaviorTest, DeathIsAnnouncedOnlyOnce) {
    Role* hero = add(t1, "英雄", 300, 500, 100);
    Role* slime = add(t2, "Slime1", 100, 0, 0);

    Waterball waterball;
    EXPECT_EQ(run(waterball, hero, {slime}), (Lines{
        "[1]英雄 對 [2]Slime1 造成 120 點傷害。",
        "[2]Slime1 死亡。",
    }));
    EXPECT_EQ(run(waterball, hero, {slime}), (Lines{"[1]英雄 對 [2]Slime1 造成 120 點傷害。"}));
}

// =====================================================================
// 自我治療
// =====================================================================

TEST_F(SkillBehaviorTest, SelfHealingAdds150HpToActorOnly) {
    Role* slime = add(t2, "Slime1", 20, 100, 30);
    Role* hero = add(t1, "英雄", 470, 500, 40);

    SelfHealing healing;
    EXPECT_TRUE(run(healing, slime, {slime}).empty());
    EXPECT_EQ(slime->getHp(), 170);
    EXPECT_EQ(slime->getMp(), 100);
    EXPECT_EQ(hero->getHp(), 470);
}

// =====================================================================
// 狀態類技能：石化、下毒、鼓舞（D10、D11）
// =====================================================================

TEST_F(SkillBehaviorTest, PetrochemicalPetrifiesTargetForThreeRounds) {
    Role* hero = add(t1, "英雄", 400, 99999, 30);
    Role* boss = add(t2, "BOSS", 270, 9999, 399);

    Petrochemical petrochemical;
    EXPECT_TRUE(run(petrochemical, hero, {boss}).empty());
    ASSERT_NE(dynamic_cast<PetrochemicaledState*>(boss->getState()), nullptr);
    EXPECT_EQ(boss->getState()->getName(), "PetrochemicaledState");
    EXPECT_EQ(boss->getState()->getRound(), 3);
    EXPECT_EQ(boss->getHp(), 270);
}

TEST_F(SkillBehaviorTest, PoisonPoisonsTargetForThreeRounds) {
    Role* hero = add(t1, "英雄", 1000, 500, 0);
    Role* slime = add(t2, "Slime1", 120, 90, 50);

    Poison poison;
    EXPECT_TRUE(run(poison, hero, {slime}).empty());
    ASSERT_NE(dynamic_cast<PoisonedState*>(slime->getState()), nullptr);
    EXPECT_EQ(slime->getState()->getName(), "PoisonedState");
    EXPECT_EQ(slime->getState()->getRound(), 3);
    EXPECT_EQ(slime->getHp(), 120); // 下毒當下不扣血，輪到時才扣
}

TEST_F(SkillBehaviorTest, CheerupCheersEveryTargetForThreeRounds) {
    Role* hero = add(t1, "英雄", 500, 10000, 30);
    Role* s1 = add(t1, "Servant1", 1000, 0, 0);
    Role* s2 = add(t1, "Servant2", 1000, 0, 0);
    Role* s3 = add(t1, "Servant3", 1000, 0, 0);

    Cheerup cheerup;
    EXPECT_TRUE(run(cheerup, hero, {s1, s2, s3}).empty());
    for (Role* servant : {s1, s2, s3}) {
        ASSERT_NE(dynamic_cast<CheerupedState*>(servant->getState()), nullptr);
        EXPECT_EQ(servant->getState()->getName(), "CheerupedState");
        EXPECT_EQ(servant->getState()->getRound(), 3);
    }
    EXPECT_NE(dynamic_cast<NormalState*>(hero->getState()), nullptr);
}

TEST_F(SkillBehaviorTest, NewStateOverwritesOldStateAndResetsRounds) {
    Role* hero = add(t1, "英雄", 500, 10000, 30);
    Role* slime = add(t2, "Slime1", 500, 0, 0);

    Poison poison;
    Petrochemical petrochemical;
    run(poison, hero, {slime});
    slime->getState()->setRound(2); // 模擬過了一回合

    run(petrochemical, hero, {slime});
    ASSERT_NE(dynamic_cast<PetrochemicaledState*>(slime->getState()), nullptr);
    EXPECT_EQ(slime->getState()->getRound(), 3);

    slime->getState()->setRound(1);
    run(petrochemical, hero, {slime}); // 相同狀態也會覆寫並重設
    EXPECT_EQ(slime->getState()->getRound(), 3);
}

TEST_F(SkillBehaviorTest, CheeredActorDealsExtra50PerDamage) {
    Role* hero = add(t1, "英雄", 500, 10000, 0);
    Role* servant = add(t1, "Servant1", 1000, 0, 0);
    Role* slime = add(t2, "Slime1", 500, 0, 0);

    Cheerup cheerup;
    run(cheerup, hero, {servant});

    BasicAttack attack;
    EXPECT_EQ(run(attack, servant, {slime}), (Lines{"[1]Servant1 對 [2]Slime1 造成 50 點傷害。"}));
    Waterball waterball;
    EXPECT_EQ(run(waterball, servant, {slime}), (Lines{"[1]Servant1 對 [2]Slime1 造成 170 點傷害。"}));
    EXPECT_EQ(slime->getHp(), 280);
}

// =====================================================================
// 召喚（Observer：SummonObserver）
// =====================================================================

TEST_F(SkillBehaviorTest, SummonAddsSlimeToTheEndOfActorsTroop) {
    Role* hero = add(t1, "英雄", 500, 10000, 30);
    add(t2, "Slime1", 1000, 0, 99);

    Summon summon;
    EXPECT_TRUE(run(summon, hero, {}).empty());

    ASSERT_EQ(static_cast<int>(t1.getRoles().size()), 2);
    EXPECT_EQ(static_cast<int>(t2.getRoles().size()), 1);
    Role* slime = t1.getRoles()[1];
    EXPECT_EQ(slime->getDisplayName(), "[1]Slime");
    EXPECT_EQ(slime->getHp(), 100);
    EXPECT_EQ(slime->getMp(), 0);
    EXPECT_EQ(slime->getStr(), 50);
    EXPECT_NE(dynamic_cast<NormalState*>(slime->getState()), nullptr);
    ASSERT_EQ(slime->getSkills().size(), 1u); // 沒有技能，只有普通攻擊
    EXPECT_EQ(slime->getSkills()[0]->getName(), "普通攻擊");

    ASSERT_EQ(slime->getObservers().size(), 1u);
    EXPECT_NE(dynamic_cast<SummonObserver*>(slime->getObservers()[0]), nullptr);
    EXPECT_EQ(slime->getObservers()[0]->getRole(), hero);
}

TEST_F(SkillBehaviorTest, EverySummonCreatesItsOwnSlime) {
    Role* hero = add(t1, "英雄", 500, 10000, 30);
    Summon summon;
    run(summon, hero, {});
    run(summon, hero, {});
    ASSERT_EQ(static_cast<int>(t1.getRoles().size()), 3);
    EXPECT_NE(t1.getRoles()[1], t1.getRoles()[2]);
    EXPECT_EQ(t1.getRoles()[2]->getObservers().size(), 1u);
}

// D40：召喚的史萊姆由 AI 操控，透過 setDecider 攜帶自己的 AIAction（seed 從 0 開始、彼此獨立）
TEST_F(SkillBehaviorTest, SummonedSlimeCarriesItsOwnAIAction) {
    Role* hero = add(t1, "英雄", 500, 10000, 30);
    Summon summon;
    run(summon, hero, {});
    run(summon, hero, {});
    Role* slime1 = t1.getRoles()[1];
    Role* slime2 = t1.getRoles()[2];

    auto* ai1 = dynamic_cast<AIAction*>(slime1->getDecider());
    auto* ai2 = dynamic_cast<AIAction*>(slime2->getDecider());
    ASSERT_NE(ai1, nullptr);
    ASSERT_NE(ai2, nullptr);
    EXPECT_NE(ai1, ai2);
    EXPECT_EQ(ai1->getSeed(), 0);

    EXPECT_EQ(slime1->getDecider()->chooseAction(slime1->getSkills())->getName(), "普通攻擊");
    EXPECT_EQ(ai1->getSeed(), 1);
    EXPECT_EQ(ai2->getSeed(), 0); // 各自的 seed 不互相影響
}

TEST_F(SkillBehaviorTest, SummonerGains30HpWhenSlimeDies) {
    Role* hero = add(t1, "英雄", 401, 10000, 30);
    Role* enemy = add(t2, "Slime1", 1000, 0, 99);

    Summon summon;
    run(summon, hero, {});
    Role* slime = t1.getRoles()[1];

    BasicAttack attack;
    EXPECT_EQ(run(attack, enemy, {slime}), (Lines{"[2]Slime1 對 [1]Slime 造成 99 點傷害。"}));
    EXPECT_EQ(hero->getHp(), 401);
    EXPECT_EQ(run(attack, enemy, {slime}), (Lines{
        "[2]Slime1 對 [1]Slime 造成 99 點傷害。",
        "[1]Slime 死亡。",
    }));
    EXPECT_EQ(hero->getHp(), 431);
}

TEST_F(SkillBehaviorTest, DeadSummonerGainsNothing) {
    Role* hero = add(t1, "英雄", 10, 10000, 30);
    Role* enemy = add(t2, "Slime1", 1000, 0, 200);

    Summon summon;
    run(summon, hero, {});
    Role* slime = t1.getRoles()[1];

    BasicAttack attack;
    run(attack, enemy, {hero});
    ASSERT_TRUE(hero->isDead());
    run(attack, enemy, {slime});
    ASSERT_TRUE(slime->isDead());
    EXPECT_EQ(hero->getHp(), 0);
}

// =====================================================================
// 自爆（D34）
// =====================================================================

TEST_F(SkillBehaviorTest, SelfExplosionHitsOthersThenActorDiesLast) {
    Role* hero = add(t1, "英雄", 999999, 500, 30);
    Role* a1 = add(t1, "A", 100, 1000, 15);
    Role* a2 = add(t2, "A", 200, 1000, 15);

    SelfExplosion explosion;
    Candidates c = explosion.getCandidates(hero, alive1(), alive2(), 1);
    EXPECT_EQ(run(explosion, hero, c.roles), (Lines{
        "[1]英雄 對 [1]A 造成 150 點傷害。",
        "[1]A 死亡。",
        "[1]英雄 對 [2]A 造成 150 點傷害。",
        "[1]英雄 死亡。", // 自己歸零不印傷害訊息，死亡訊息最後才印
    }));
    EXPECT_TRUE(hero->isDead());
    EXPECT_TRUE(a1->isDead());
    EXPECT_EQ(a2->getHp(), 50);
}

TEST_F(SkillBehaviorTest, SelfExplosionDeathTriggersObservers) {
    Role* curser = add(t2, "Curser", 1000, 0, 0);
    Role* hero = add(t1, "英雄", 1000, 500, 0);

    Curse curse;
    run(curse, curser, {hero});
    SelfExplosion explosion;
    EXPECT_EQ(run(explosion, hero, {curser}), (Lines{
        "[1]英雄 對 [2]Curser 造成 150 點傷害。",
        "[1]英雄 死亡。",
    }));
    // 自爆的自殺也經過 lossHp → 通知觀察者（D17）；MP 由 State 流程扣，這裡仍是 500
    EXPECT_EQ(curser->getHp(), 1000 - 150 + 500);
}

TEST_F(SkillBehaviorTest, CurserKilledByExplosionGainsNothing) {
    Role* curser = add(t2, "Curser", 100, 0, 0);
    Role* hero = add(t1, "英雄", 1000, 500, 0);

    Curse curse;
    run(curse, curser, {hero});
    SelfExplosion explosion;
    run(explosion, hero, {curser});
    EXPECT_TRUE(hero->isDead());
    EXPECT_EQ(curser->getHp(), 0);
}

// =====================================================================
// 詛咒（Observer：CurserObserver，D18、D19）
// =====================================================================

TEST_F(SkillBehaviorTest, CurseFromSameCurserDoesNotStack) {
    Role* a = add(t1, "A", 500, 500, 50);
    Role* b = add(t1, "B", 500, 500, 50);
    Role* target = add(t2, "T", 500, 500, 50);

    Curse curse;
    EXPECT_TRUE(run(curse, a, {target}).empty());
    run(curse, b, {target});
    run(curse, a, {target});

    ASSERT_EQ(target->getObservers().size(), 2u);
    EXPECT_EQ(target->getObservers()[0]->getRole(), a);
    EXPECT_EQ(target->getObservers()[1]->getRole(), b);
    EXPECT_EQ(target->getHp(), 500);
}

TEST_F(SkillBehaviorTest, EachDifferentCurserGainsRemainingMpOnDeath) {
    // 需求範例：依序被 A、B、A 詛咒，死亡時剩 60 MP → A、B 各 + 60
    Role* a = add(t1, "A", 100, 500, 50);
    Role* b = add(t1, "B", 200, 500, 50);
    Role* target = add(t2, "T", 10, 60, 0);

    Curse curse;
    run(curse, a, {target});
    run(curse, b, {target});
    run(curse, a, {target});

    Waterball waterball;
    run(waterball, a, {target});
    ASSERT_TRUE(target->isDead());
    EXPECT_EQ(a->getHp(), 160);
    EXPECT_EQ(b->getHp(), 260);
}

TEST_F(SkillBehaviorTest, DeadCurserGainsNothing) {
    Role* curser = add(t1, "Curser", 10, 500, 0);
    Role* target = add(t2, "T", 10, 999, 100);

    Curse curse;
    run(curse, curser, {target});
    BasicAttack attack;
    run(attack, target, {curser});
    ASSERT_TRUE(curser->isDead());

    Waterball waterball;
    Role* hero = add(t1, "英雄", 100, 500, 0);
    run(waterball, hero, {target});
    ASSERT_TRUE(target->isDead());
    EXPECT_EQ(curser->getHp(), 0);
}

TEST_F(SkillBehaviorTest, CursedRoleDyingFromOtherHpLossStillRewardsCurser) {
    Role* hero = add(t1, "英雄", 300, 10000, 100);
    Role* slime = add(t2, "Slime", 30, 999, 0);

    Curse curse;
    run(curse, hero, {slime});
    {
        CoutCapture capture;
        slime->lossHp(30); // 例如中毒扣血：所有 HP 減少都走 lossHp（D17）
        EXPECT_EQ(capture.lines(), (Lines{"[2]Slime 死亡。"}));
    }
    EXPECT_EQ(hero->getHp(), 300 + 999);
}

// =====================================================================
// 一拳攻擊（Chain of Responsibility，D21–D25）
// =====================================================================

TEST_F(SkillBehaviorTest, OnePunchDeals300WhenTargetHpAtLeast500) {
    Role* hero = add(t1, "英雄", 1000, 10000, 0);
    Role* slime = add(t2, "Slime1", 601, 0, 0);

    OnePunch punch(requirementChain());
    EXPECT_EQ(run(punch, hero, {slime}), (Lines{"[1]英雄 對 [2]Slime1 造成 300 點傷害。"}));
    EXPECT_EQ(slime->getHp(), 301);

    Role* exactly500 = add(t2, "Slime2", 500, 0, 0);
    EXPECT_EQ(run(punch, hero, {exactly500}), (Lines{"[1]英雄 對 [2]Slime2 造成 300 點傷害。"}));
}

TEST_F(SkillBehaviorTest, OnePunchHitsPoisonedOrPetrifiedTargetThreeTimes) {
    Role* hero = add(t1, "英雄", 1000, 10000, 0);
    Role* poisoned = add(t2, "Slime2", 300, 0, 0);
    Role* petrified = add(t2, "Slime3", 300, 0, 0);
    poisoned->setState(new PoisonedState());
    petrified->setState(new PetrochemicaledState());

    OnePunch punch(requirementChain());
    EXPECT_EQ(run(punch, hero, {poisoned}), (Lines{
        "[1]英雄 對 [2]Slime2 造成 80 點傷害。",
        "[1]英雄 對 [2]Slime2 造成 80 點傷害。",
        "[1]英雄 對 [2]Slime2 造成 80 點傷害。",
    }));
    EXPECT_EQ(poisoned->getHp(), 60);
    run(punch, hero, {petrified});
    EXPECT_EQ(petrified->getHp(), 60);
}

// §7.2 I4（2026-10-14 依 testcases/one-punch.out 修正）：目標在第 2 下死亡 → 不再打第 3 下
TEST_F(SkillBehaviorTest, OnePunchStopsHittingOnceTargetDies) {
    Role* hero = add(t1, "英雄", 1000, 10000, 0);
    Role* slime = add(t2, "Slime1", 160, 0, 0);
    slime->setState(new PoisonedState());

    OnePunch punch(requirementChain());
    EXPECT_EQ(run(punch, hero, {slime}), (Lines{
        "[1]英雄 對 [2]Slime1 造成 80 點傷害。",
        "[1]英雄 對 [2]Slime1 造成 80 點傷害。",
        "[2]Slime1 死亡。",
    }));
    EXPECT_EQ(slime->getHp(), 0);
}

TEST_F(SkillBehaviorTest, OnePunchOnCheeredTargetDeals100AndResetsToNormal) {
    Role* hero = add(t1, "英雄", 400, 10000, 0);
    Role* slime = add(t2, "Slime1", 201, 0, 0);
    slime->setState(new CheerupedState());

    OnePunch punch(requirementChain());
    EXPECT_EQ(run(punch, hero, {slime}), (Lines{"[1]英雄 對 [2]Slime1 造成 100 點傷害。"}));
    EXPECT_EQ(slime->getHp(), 101);
    ASSERT_NE(dynamic_cast<NormalState*>(slime->getState()), nullptr);
}

TEST_F(SkillBehaviorTest, OnePunchOnNormalTargetDeals100) {
    Role* hero = add(t1, "英雄", 400, 10000, 0);
    Role* slime = add(t2, "Slime1", 301, 0, 0);

    OnePunch punch(requirementChain());
    EXPECT_EQ(run(punch, hero, {slime}), (Lines{"[1]英雄 對 [2]Slime1 造成 100 點傷害。"}));
    EXPECT_EQ(slime->getHp(), 201);
}

TEST_F(SkillBehaviorTest, OnePunchUsesOnlyTheFirstMatchingRule) {
    Role* hero = add(t1, "英雄", 1000, 10000, 0);
    Role* slime = add(t2, "Slime1", 800, 0, 0);
    slime->setState(new PoisonedState()); // HP ≥ 500 且中毒 → 只套用第一條（300）

    OnePunch punch(requirementChain());
    EXPECT_EQ(run(punch, hero, {slime}), (Lines{"[1]英雄 對 [2]Slime1 造成 300 點傷害。"}));
    EXPECT_EQ(slime->getHp(), 500);
    EXPECT_NE(dynamic_cast<PoisonedState*>(slime->getState()), nullptr);
}

TEST_F(SkillBehaviorTest, OnePunchFromCheeredActorAdds50ToEveryHit) {
    Role* hero = add(t1, "英雄", 1000, 10000, 0);
    Role* slime = add(t2, "Slime1", 400, 0, 0);
    hero->setState(new CheerupedState());
    slime->setState(new PoisonedState());

    OnePunch punch(requirementChain());
    EXPECT_EQ(run(punch, hero, {slime}), (Lines{ // D15：每一下都 +50
        "[1]英雄 對 [2]Slime1 造成 130 點傷害。",
        "[1]英雄 對 [2]Slime1 造成 130 點傷害。",
        "[1]英雄 對 [2]Slime1 造成 130 點傷害。",
    }));
    EXPECT_EQ(slime->getHp(), 10);
}

TEST_F(SkillBehaviorTest, OnePunchWithoutHandlersDoesNothing) {
    Role* hero = add(t1, "英雄", 1000, 10000, 0);
    Role* slime = add(t2, "Slime1", 601, 0, 0);

    OnePunch punch({});
    EXPECT_TRUE(run(punch, hero, {slime}).empty());
    EXPECT_EQ(slime->getHp(), 601);
}

// 需求 ④：Client 可以從外部加入新規則（不改 OnePunch），且規則可依「狀態以外的屬性」判斷
class HighMpHandler : public OnePunchHandler {
public:
    bool match(Role* actor, Role* target) override { return target->getMp() >= 999; }
    void doHandle(Role* actor, Role* target) override { actor->getState()->doDamage(target, 1); }
};

TEST_F(SkillBehaviorTest, OnePunchAcceptsHandlersInjectedByClient) {
    Role* hero = add(t1, "英雄", 1000, 10000, 0);
    Role* mage = add(t2, "Mage", 900, 999, 0);
    Role* slime = add(t2, "Slime", 900, 0, 0);

    std::vector<OnePunchHandler*> chain = requirementChain();
    chain.insert(chain.begin(), new HighMpHandler());
    OnePunch punch(chain);

    EXPECT_EQ(run(punch, hero, {mage}), (Lines{"[1]英雄 對 [2]Mage 造成 1 點傷害。"}));
    EXPECT_EQ(run(punch, hero, {slime}), (Lines{"[1]英雄 對 [2]Slime 造成 300 點傷害。"}));
}

} // namespace

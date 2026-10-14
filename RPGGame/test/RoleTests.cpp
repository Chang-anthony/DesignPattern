/*
 * Role 與 Observer 的單元測試。
 *  - 依據：need/need.txt、CLAUDE.md 決策 D4、D6、D9–D11、D14、D17、D18、D28
 *  - 輸出以 rdbuf 導向字串收集（D38）
 */
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Role.hpp"
#include "Troop.hpp"
#include "IAction.hpp"
#include "Skill.hpp"
#include "BasicAttack.hpp"
#include "Waterball.hpp"
#include "Fireball.hpp"
#include "Curse.hpp"
#include "State.hpp"
#include "NormalState.hpp"
#include "PoisonedState.hpp"
#include "PetrochemicaledState.hpp"
#include "CheerupedState.hpp"
#include "SkillObserver.hpp"
#include "SummonObserver.hpp"
#include "CurserObserver.hpp"
#include "Slime.hpp"

namespace {

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

using Lines = std::vector<std::string>;

// 記錄 decision() 收到的參數，用來確認 Role::takeTurn 交給目前的狀態（D10）
class RecordingState : public State {
public:
    RecordingState() { displayName = "測試"; }

    int calls = 0;
    std::vector<Role*> lastT1;
    std::vector<Role*> lastT2;
    int lastSide = 0;

    void decision(const std::vector<Role*>& t1, const std::vector<Role*>& t2, int actorSide) override {
        calls++;
        lastT1 = t1;
        lastT2 = t2;
        lastSide = actorSide;
    }
};

// 記錄被通知的順序（D18：pull model，只收到死者）
class RecordingObserver : public SkillObserver {
public:
    RecordingObserver(Role* actor, std::vector<std::string>* log, std::string tag)
        : SkillObserver(actor), log(log), tag(std::move(tag)) {}

    void UntilDie(Role* dead) override { log->push_back(tag + ":" + dead->getName()); }

private:
    std::vector<std::string>* log;
    std::string tag;
};

class DummyAction : public IAction {
public:
    Skill* chooseAction(const std::vector<Skill*>& skills) override { return skills.front(); }
    std::vector<Role*> chooseTargets(const std::vector<Role*>& candidates, int) override { return candidates; }
};

class RoleTest : public ::testing::Test {
protected:
    Troop t1{1};
    Troop t2{2};

    Role* add(Troop& troop, const std::string& name, int hp, int mp, int str) {
        Role* role = new Role(hp, mp, str, name);
        troop.addRole(role);
        return role;
    }
};

// =====================================================================
// 基本屬性
// =====================================================================

TEST_F(RoleTest, StartsInNormalStateWithBasicAttackFirst) {
    Role role(100, 50, 10, "A", {new Fireball(), new Curse()});
    ASSERT_NE(dynamic_cast<NormalState*>(role.getState()), nullptr);
    EXPECT_EQ(role.getState()->getRole(), &role);
    ASSERT_EQ(role.getSkills().size(), 3u);
    EXPECT_NE(dynamic_cast<BasicAttack*>(role.getSkills()[0]), nullptr); // D28
    EXPECT_EQ(role.getSkills()[1]->getName(), "火球");
    EXPECT_EQ(role.getSkills()[2]->getName(), "詛咒");
    EXPECT_EQ(role.getHp(), 100);
    EXPECT_EQ(role.getMp(), 50);
    EXPECT_EQ(role.getStr(), 10);
    EXPECT_FALSE(role.isDead());
}

TEST_F(RoleTest, DisplayNameUsesTroopId) {
    Role* hero = add(t1, "英雄", 100, 0, 0);
    Role* boss = add(t2, "BOSS", 100, 0, 0);
    EXPECT_EQ(hero->getDisplayName(), "[1]英雄");
    EXPECT_EQ(boss->getDisplayName(), "[2]BOSS");
    EXPECT_EQ(hero->getTroop(), &t1);
}

TEST_F(RoleTest, RemoveRoleDetachesRoleFromTroop) {
    Role* hero = add(t1, "英雄", 100, 0, 0);
    Role* ally = add(t1, "Ally", 100, 0, 0);

    EXPECT_NO_THROW(t1.removeRole(ally));
    EXPECT_EQ(t1.getRoles(), (std::vector<Role*>{hero}));
    EXPECT_EQ(ally->getTroop(), nullptr);
    EXPECT_EQ(ally->getDisplayName(), "Ally"); // 不再帶軍隊前綴
    EXPECT_EQ(hero->getTroop(), &t1);
}

// =====================================================================
// 英雄識別（D6）與決策者（D4）
// =====================================================================

TEST_F(RoleTest, OnlyRoleMarkedWithHIsHero) {
    Role hero(300, 500, 100, "英雄");
    Role slime(200, 60, 49, "Slime1");
    EXPECT_FALSE(hero.isHero());
    hero.setIdentity('h');
    EXPECT_TRUE(hero.isHero());
    EXPECT_EQ(hero.getIdentity(), 'h');
    EXPECT_FALSE(slime.isHero());
}

TEST_F(RoleTest, HoldsItsDecider) {
    Role role(100, 0, 0, "A");
    EXPECT_EQ(role.getDecider(), nullptr);
    DummyAction decider;
    role.setDecider(&decider);
    EXPECT_EQ(role.getDecider(), &decider);
    EXPECT_THROW(role.setDecider(nullptr), std::invalid_argument);
}

// =====================================================================
// MP（D9）
// =====================================================================

TEST_F(RoleTest, CheckMpOnlyChecksAndPrintsNothing) {
    Role role(100, 60, 0, "Slime1");
    Fireball fireball;   // 50
    Waterball waterball; // 50
    Curse curse;         // 100

    CoutCapture capture;
    EXPECT_TRUE(role.checkMp(&fireball));
    EXPECT_TRUE(role.checkMp(&waterball));
    EXPECT_FALSE(role.checkMp(&curse));
    EXPECT_TRUE(role.checkMp(role.getSkills()[0])); // 普通攻擊 MP 0
    EXPECT_EQ(role.getMp(), 60);                      // 不扣除
    EXPECT_TRUE(capture.lines().empty());             // 「你缺乏 MP」由流程印，不是 Role
}

TEST_F(RoleTest, CheckMpBoundaryIsInclusive) {
    Role role(100, 50, 0, "A");
    Fireball fireball;
    EXPECT_TRUE(role.checkMp(&fireball)); // MP 剛好等於花費也可以施放
    role.lossMp(1);
    EXPECT_FALSE(role.checkMp(&fireball));
}

TEST_F(RoleTest, LossAndGainMp) {
    Role role(100, 500, 0, "英雄");
    role.lossMp(50);
    EXPECT_EQ(role.getMp(), 450);
    role.gainMp(10);
    EXPECT_EQ(role.getMp(), 460);
}

// =====================================================================
// HP 與死亡（D14、D17）
// =====================================================================

TEST_F(RoleTest, LossHpAnnouncesDeathOnlyWhenHpReachesZero) {
    Role* slime = add(t2, "Slime1", 100, 0, 0);
    {
        CoutCapture capture;
        slime->lossHp(99);
        EXPECT_TRUE(capture.lines().empty());
    }
    EXPECT_EQ(slime->getHp(), 1);
    {
        CoutCapture capture;
        slime->lossHp(1);
        EXPECT_EQ(capture.lines(), (Lines{"[2]Slime1 死亡。"}));
    }
    EXPECT_TRUE(slime->isDead());
    {
        CoutCapture capture;
        slime->lossHp(10); // 已死亡：不再印、不再通知
        EXPECT_TRUE(capture.lines().empty());
    }
}

TEST_F(RoleTest, GainHpHasNoCap) {
    Role role(500, 0, 0, "A");
    role.gainHp(150);
    EXPECT_EQ(role.getHp(), 650);
}

// =====================================================================
// 觀察者（D18）
// =====================================================================

TEST_F(RoleTest, ObserversAreNotifiedOnceInTheOrderTheyWereAdded) {
    Role* a = add(t1, "A", 100, 0, 0);
    Role* b = add(t1, "B", 100, 0, 0);
    Role* target = add(t2, "T", 10, 60, 0);
    std::vector<std::string> log;
    target->addObserver(new RecordingObserver(a, &log, "a"));
    target->addObserver(new RecordingObserver(b, &log, "b"));

    CoutCapture mute;
    target->lossHp(10);
    target->lossHp(10);
    EXPECT_EQ(log, (std::vector<std::string>{"a:T", "b:T"}));
}

TEST_F(RoleTest, RemovedObserverIsNotNotified) {
    Role* a = add(t1, "A", 100, 0, 0);
    Role* target = add(t2, "T", 10, 0, 0);
    std::vector<std::string> log;
    auto* observer = new RecordingObserver(a, &log, "a");
    target->addObserver(observer);
    target->removeObserver(observer);
    EXPECT_TRUE(target->getObservers().empty());

    CoutCapture mute;
    target->lossHp(10);
    EXPECT_TRUE(log.empty());
}

TEST_F(RoleTest, ObserverRewardsAreAppliedAfterDeathMessage) {
    Role* curser = add(t1, "Curser", 100, 0, 0);
    Role* summoner = add(t1, "Summoner", 100, 0, 0);
    Role* target = add(t2, "T", 10, 70, 0);
    target->addObserver(new CurserObserver(curser));
    target->addObserver(new SummonObserver(summoner));

    CoutCapture capture;
    target->lossHp(10);
    EXPECT_EQ(capture.lines(), (Lines{"[2]T 死亡。"}));
    EXPECT_EQ(curser->getHp(), 170);   // + 剩餘 MP
    EXPECT_EQ(summoner->getHp(), 130); // + 30
}

TEST_F(RoleTest, DeadObserverOwnersGetNoReward) {
    Role* curser = add(t1, "Curser", 10, 0, 0);
    Role* summoner = add(t1, "Summoner", 10, 0, 0);
    Role* target = add(t2, "T", 10, 70, 0);
    target->addObserver(new CurserObserver(curser));
    target->addObserver(new SummonObserver(summoner));

    CoutCapture mute;
    curser->lossHp(10);
    summoner->lossHp(10);
    target->lossHp(10);
    EXPECT_EQ(curser->getHp(), 0);
    EXPECT_EQ(summoner->getHp(), 0);
}

// =====================================================================
// 狀態（D10、D11）
// =====================================================================

TEST_F(RoleTest, SetStateReplacesStateAndBindsRole) {
    Role role(100, 0, 0, "A");
    role.setState(new PoisonedState());
    ASSERT_NE(dynamic_cast<PoisonedState*>(role.getState()), nullptr);
    EXPECT_EQ(role.getState()->getRole(), &role);
    EXPECT_EQ(role.getState()->getRound(), 3);
}

TEST_F(RoleTest, TakeTurnHandsTheBattlefieldToCurrentState) {
    Role* hero = add(t1, "英雄", 100, 0, 0);
    Role* slime = add(t2, "Slime1", 100, 0, 0);
    auto* state = new RecordingState();
    hero->setState(state);

    {
        CoutCapture capture;
        hero->takeTurn(t1.getRoles(), t2.getRoles(), 1);
        // 「輪到 …」由 Role 在交給狀態之前印（§7.2 I6）
        EXPECT_EQ(capture.lines(), (Lines{"輪到 [1]英雄 (HP: 100, MP: 0, STR: 0, State: 測試)。"}));
    }
    EXPECT_EQ(state->calls, 1);
    EXPECT_EQ(state->lastT1, (std::vector<Role*>{hero}));
    EXPECT_EQ(state->lastT2, (std::vector<Role*>{slime}));
    EXPECT_EQ(state->lastSide, 1);
}

TEST_F(RoleTest, NormalStateHasNoCountdown) {
    Role role(100, 0, 0, "A");
    State* before = role.getState();
    role.endThisRound();
    role.endThisRound();
    EXPECT_EQ(role.getState(), before);
    EXPECT_NE(dynamic_cast<NormalState*>(role.getState()), nullptr);
}

TEST_F(RoleTest, TimedStatesReturnToNormalAfterThreeRoundEnds) {
    std::vector<State*> states = {new PetrochemicaledState(), new PoisonedState(), new CheerupedState()};
    for (State* timed : states) {
        Role role(100, 0, 0, "A");
        role.setState(timed);
        SCOPED_TRACE(timed->getName());
        role.endThisRound();
        EXPECT_EQ(role.getState()->getRound(), 2);
        role.endThisRound();
        EXPECT_EQ(role.getState()->getRound(), 1);
        EXPECT_EQ(role.getState(), timed); // 還沒到期
        role.endThisRound();
        ASSERT_NE(dynamic_cast<NormalState*>(role.getState()), nullptr);
        EXPECT_EQ(role.getState()->getRole(), &role);
    }
}

TEST_F(RoleTest, OverwrittenStateRestartsCountdown) {
    Role role(100, 0, 0, "A");
    role.setState(new PoisonedState());
    role.endThisRound();
    role.endThisRound(); // 剩 1 回合
    role.setState(new PetrochemicaledState());
    role.endThisRound();
    role.endThisRound();
    EXPECT_NE(dynamic_cast<PetrochemicaledState*>(role.getState()), nullptr);
    role.endThisRound();
    EXPECT_NE(dynamic_cast<NormalState*>(role.getState()), nullptr);
}

TEST_F(RoleTest, CheerupBonusEndsWhenStateExpires) {
    Role* servant = add(t1, "Servant1", 1000, 0, 0);
    Role* slime = add(t2, "Slime1", 500, 0, 0);
    servant->setState(new CheerupedState());
    BasicAttack attack;
    {
        CoutCapture capture;
        attack.attack(servant, {slime});
        EXPECT_EQ(capture.lines(), (Lines{"[1]Servant1 對 [2]Slime1 造成 50 點傷害。"}));
    }
    servant->endThisRound();
    servant->endThisRound();
    servant->endThisRound();
    {
        CoutCapture capture;
        attack.attack(servant, {slime}); // 回到正常狀態，傷害還原為 STR（0）
        EXPECT_EQ(capture.lines(), (Lines{"[1]Servant1 對 [2]Slime1 造成 0 點傷害。"}));
    }
}

// =====================================================================
// 史萊姆（D43、D44）
// =====================================================================

TEST_F(RoleTest, SlimeHasTheStatsGivenByRequirement) {
    // 需求「召喚」：史萊姆擁有 100 HP、0 MP、50 STR，沒有任何技能，並且初始為正常狀態
    Slime slime;
    EXPECT_EQ(slime.getName(), "Slime");
    EXPECT_EQ(slime.getHp(), 100);
    EXPECT_EQ(slime.getMp(), 0);
    EXPECT_EQ(slime.getStr(), 50);
    ASSERT_EQ(slime.getSkills().size(), 1u);
    EXPECT_NE(dynamic_cast<BasicAttack*>(slime.getSkills()[0]), nullptr); // 只有普通攻擊（D28）
    EXPECT_NE(dynamic_cast<NormalState*>(slime.getState()), nullptr);
    EXPECT_FALSE(slime.isHero());
    EXPECT_EQ(slime.getDecider(), nullptr); // 決策者由 Summon 裝上（D40）
}

} // namespace

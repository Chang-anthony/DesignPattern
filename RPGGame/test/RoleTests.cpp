/*
 * Role 與 Observer 的單元測試。
 *  - 依據：need/need.txt、CLAUDE.md 決策 D4、D6、D9–D11、D14、D17、D18、D28
 *  - 輸出以 io::setOutput 導向字串收集（D50；原本用 rdbuf，D38）
 */
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

#include "Output.hpp"
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

// 編譯期檢查（D47）：從外部（例如技能）能不能直接呼叫這些函式
template <class R> concept CanCallLossHp = requires(R& r) { r.lossHp(1); };
template <class S> concept CanCallDamage = requires(S& s) { s.damage(1); };
template <class S> concept CanCallDoDamage = requires(S& s, Role* target) { s.doDamage(target, 1); };

// 在作用域內把模組輸出（io::output()）導向字串，解構時還原（D50）
class OutputCapture {
public:
    OutputCapture() : sink(buffer), previous(io::setOutput(&sink)) {}
    ~OutputCapture() { io::setOutput(previous); }

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
    io::StreamOutput sink;
    io::Output* previous;
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

// 擁有權測試用（D49）：被 delete 時把旗標設為 true
class TrackedAction : public DummyAction {
public:
    explicit TrackedAction(bool* destroyed) : destroyed(destroyed) {}
    ~TrackedAction() override { *destroyed = true; }

private:
    bool* destroyed;
};

class TrackedObserver : public SkillObserver {
public:
    TrackedObserver(Role* actor, bool* destroyed) : SkillObserver(actor), destroyed(destroyed) {}
    ~TrackedObserver() override { *destroyed = true; }
    void UntilDie(Role*) override {}

private:
    bool* destroyed;
};

class TrackedRole : public Role {
public:
    TrackedRole(const std::string& name, bool* destroyed) : Role(100, 0, 0, name), destroyed(destroyed) {}
    ~TrackedRole() override { *destroyed = true; }

private:
    bool* destroyed;
};

class RoleTest : public ::testing::Test {
protected:
    Troop t1{1};
    Troop t2{2};
    Role attacker{1, 0, 0, "Attacker"}; // 不在任何軍隊：輸出名稱沒有前綴

    // 讓 target 受到 n 點傷害：Role::lossHp 不公開（D47），測試也走正規通道 doDamage
    void hurt(Role* target, int n) { attacker.getState()->doDamage(target, n); }

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
    delete ally; // 移出軍隊後擁有權交回呼叫端（D49）
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
    DummyAction* decider = new DummyAction(); // Role 擁有決策者（D49）
    role.setDecider(decider);
    EXPECT_EQ(role.getDecider(), decider);
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

    OutputCapture capture;
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
        OutputCapture capture;
        hurt(slime, 99);
        EXPECT_EQ(capture.lines(), (Lines{"Attacker 對 [2]Slime1 造成 99 點傷害。"})); // 沒有死亡訊息
    }
    EXPECT_EQ(slime->getHp(), 1);
    {
        OutputCapture capture;
        hurt(slime, 1);
        EXPECT_EQ(capture.lines(), (Lines{"Attacker 對 [2]Slime1 造成 1 點傷害。", "[2]Slime1 死亡。"}));
    }
    EXPECT_TRUE(slime->isDead());
    {
        OutputCapture capture;
        hurt(slime, 10); // 已死亡：只有傷害訊息，不再印死亡、不再通知
        EXPECT_EQ(capture.lines(), (Lines{"Attacker 對 [2]Slime1 造成 10 點傷害。"}));
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

    OutputCapture mute;
    hurt(target, 10);
    hurt(target, 10);
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
    delete observer; // 移除後擁有權交回呼叫端（D49）

    OutputCapture mute;
    hurt(target, 10);
    EXPECT_TRUE(log.empty());
}

TEST_F(RoleTest, ObserverRewardsAreAppliedAfterDeathMessage) {
    Role* curser = add(t1, "Curser", 100, 0, 0);
    Role* summoner = add(t1, "Summoner", 100, 0, 0);
    Role* target = add(t2, "T", 10, 70, 0);
    target->addObserver(new CurserObserver(curser));
    target->addObserver(new SummonObserver(summoner));

    OutputCapture capture;
    hurt(target, 10);
    EXPECT_EQ(capture.lines(), (Lines{"Attacker 對 [2]T 造成 10 點傷害。", "[2]T 死亡。"})); // 獎勵本身不印訊息
    EXPECT_EQ(curser->getHp(), 170);   // + 剩餘 MP
    EXPECT_EQ(summoner->getHp(), 130); // + 30
}

TEST_F(RoleTest, DeadObserverOwnersGetNoReward) {
    Role* curser = add(t1, "Curser", 10, 0, 0);
    Role* summoner = add(t1, "Summoner", 10, 0, 0);
    Role* target = add(t2, "T", 10, 70, 0);
    target->addObserver(new CurserObserver(curser));
    target->addObserver(new SummonObserver(summoner));

    OutputCapture mute;
    hurt(curser, 10);
    hurt(summoner, 10);
    hurt(target, 10);
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
        OutputCapture capture;
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
        OutputCapture capture;
        attack.attack(servant, {slime});
        EXPECT_EQ(capture.lines(), (Lines{"[1]Servant1 對 [2]Slime1 造成 50 點傷害。"}));
    }
    servant->endThisRound();
    servant->endThisRound();
    servant->endThisRound();
    {
        OutputCapture capture;
        attack.attack(servant, {slime}); // 回到正常狀態，傷害還原為 STR（0）
        EXPECT_EQ(capture.lines(), (Lines{"[1]Servant1 對 [2]Slime1 造成 0 點傷害。"}));
    }
}

// =====================================================================
// 傷害只有一個公開通道（D47）
// =====================================================================

TEST_F(RoleTest, DoDamageIsTheOnlyPublicWayToReduceHp) {
    // 這三行在編譯期就決定結果：若有人把 lossHp / damage 改回 public，測試會編譯失敗
    static_assert(!CanCallLossHp<Role>, "Role::lossHp must not be public");
    static_assert(!CanCallDamage<State>, "State::damage must not be public");
    static_assert(CanCallDoDamage<State>, "State::doDamage is the public damage channel");
    SUCCEED();
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

// =====================================================================
// 擁有權（D49）：Client → Troop → Role → 狀態 / 技能 / 觀察者 / 決策者
// =====================================================================

TEST_F(RoleTest, TroopReleasesItsRolesButNotRemovedOnes) {
    // 擁有裸指標的類別不能複製，否則兩份解構子會重複釋放
    static_assert(!std::is_copy_constructible_v<Troop> && !std::is_copy_assignable_v<Troop>);
    static_assert(!std::is_copy_constructible_v<Role> && !std::is_copy_assignable_v<Role>);

    bool keptDestroyed = false, removedDestroyed = false;
    TrackedRole* removed = new TrackedRole("Removed", &removedDestroyed);
    {
        Troop troop(1);
        troop.addRole(new TrackedRole("Kept", &keptDestroyed));
        troop.addRole(removed);
        troop.removeRole(removed);
    }
    EXPECT_TRUE(keptDestroyed);     // 軍隊解構時一併釋放
    EXPECT_FALSE(removedDestroyed); // 已移出：擁有權交回呼叫端
    delete removed;
    EXPECT_TRUE(removedDestroyed);
}

TEST_F(RoleTest, RoleReleasesItsObserversAndDecider) {
    bool observerDestroyed = false, deciderDestroyed = false;
    {
        Role role(100, 0, 0, "A");
        role.addObserver(new TrackedObserver(&attacker, &observerDestroyed));
        role.setDecider(new TrackedAction(&deciderDestroyed));
    }
    EXPECT_TRUE(observerDestroyed);
    EXPECT_TRUE(deciderDestroyed);
}

TEST_F(RoleTest, ReplacingDeciderReleasesOnlyTheOldOne) {
    bool firstDestroyed = false, secondDestroyed = false;
    Role role(100, 0, 0, "A");
    TrackedAction* first = new TrackedAction(&firstDestroyed);
    role.setDecider(first);
    role.setDecider(first); // 設同一個：不能釋放自己
    EXPECT_FALSE(firstDestroyed);
    EXPECT_EQ(role.getDecider(), first);

    role.setDecider(new TrackedAction(&secondDestroyed));
    EXPECT_TRUE(firstDestroyed); // 換掉的舊決策者被釋放
    EXPECT_FALSE(secondDestroyed);
}

} // namespace

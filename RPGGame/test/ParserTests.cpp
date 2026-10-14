/*
 * RPG_parser（Client 端的輸入解析與技能建造函式）的單元測試。
 *  - 依據：need/need.md「輸入格式」、CLAUDE.md 決策 D6、D21、D26、D28、D36、D37、D40
 */
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "RPG_parser.hpp"
#include "Troop.hpp"
#include "Role.hpp"
#include "AIAction.hpp"
#include "Skill.hpp"
#include "OnePunch.hpp"

namespace {

using Names = std::vector<std::string>;

Names skillNames(const Role* role) {
    Names names;
    for (const Skill* skill : role->getSkills()) names.push_back(skill->getName());
    return names;
}

const char* kInput =
    "#軍隊-1-開始\n"
    "英雄 300 500 100 火球 水球\n"
    "Ally 100 0 10\n"
    "#軍隊-1-結束\n"
    "#軍隊-2-開始\n"
    "攻擊力超強的BOSS 270 9999 399 石化 自爆\n"
    "#軍隊-2-結束\n"
    "1\n"
    "0, 1\n";

TEST(ParserTest, ParsesBothTroops) {
    std::istringstream input(kInput);
    RPGSetup setup = RPG_parser::parse(input);

    EXPECT_EQ(setup.t1->getId(), 1);
    EXPECT_EQ(setup.t2->getId(), 2);
    ASSERT_EQ(setup.t1->getRoles().size(), 2u);
    ASSERT_EQ(setup.t2->getRoles().size(), 1u);

    Role* hero = setup.t1->getRoles()[0];
    EXPECT_EQ(hero->getDisplayName(), "[1]英雄");
    EXPECT_EQ(hero->getHp(), 300);
    EXPECT_EQ(hero->getMp(), 500);
    EXPECT_EQ(hero->getStr(), 100);
    EXPECT_EQ(skillNames(hero), (Names{"普通攻擊", "火球", "水球"})); // 普通攻擊由 Role 自動加入（D28）

    Role* ally = setup.t1->getRoles()[1];
    EXPECT_EQ(ally->getDisplayName(), "[1]Ally");
    EXPECT_EQ(skillNames(ally), (Names{"普通攻擊"})); // 沒有技能

    Role* boss = setup.t2->getRoles()[0];
    EXPECT_EQ(boss->getDisplayName(), "[2]攻擊力超強的BOSS");
    EXPECT_EQ(boss->getHp(), 270);
    EXPECT_EQ(boss->getMp(), 9999);
    EXPECT_EQ(boss->getStr(), 399);
    EXPECT_EQ(skillNames(boss), (Names{"普通攻擊", "石化", "自爆"}));
}

TEST(ParserTest, FirstRoleOfTroop1IsTheHeroAndOthersAreAI) {
    std::istringstream input(kInput);
    RPGSetup setup = RPG_parser::parse(input);

    Role* hero = setup.t1->getRoles()[0];
    EXPECT_EQ(setup.hero, hero);
    EXPECT_TRUE(hero->isHero());                      // D6
    EXPECT_EQ(hero->getDecider(), nullptr);           // 英雄的決策來源由呼叫端決定（D37）
    for (Role* role : {setup.t1->getRoles()[1], setup.t2->getRoles()[0]}) {
        SCOPED_TRACE(role->getName());
        EXPECT_FALSE(role->isHero());
        EXPECT_NE(dynamic_cast<AIAction*>(role->getDecider()), nullptr); // 英雄以外由 AI 操控
    }
    EXPECT_NE(setup.t1->getRoles()[1]->getDecider(), setup.t2->getRoles()[0]->getDecider()); // 每人一個 AI
}

TEST(ParserTest, StopsRightAfterTroop2SoHeroDecisionsRemain) {
    std::istringstream input(kInput);
    RPG_parser::parse(input);
    std::string line;
    ASSERT_TRUE(std::getline(input, line));
    EXPECT_EQ(line, "1");
    ASSERT_TRUE(std::getline(input, line));
    EXPECT_EQ(line, "0, 1");
}

TEST(ParserTest, AcceptsWindowsLineEndingsAndBlankLines) {
    std::istringstream input(
        "\r\n#軍隊-1-開始\r\n英雄 300 500 100 火球\r\n\r\n#軍隊-1-結束\r\n"
        "#軍隊-2-開始\r\nSlime1 200 60 49\r\n#軍隊-2-結束\r\n1\r\n");
    RPGSetup setup = RPG_parser::parse(input);
    EXPECT_EQ(skillNames(setup.hero), (Names{"普通攻擊", "火球"}));
    EXPECT_EQ(setup.t2->getRoles()[0]->getName(), "Slime1"); // 名稱沒有殘留 '\r'
    EXPECT_EQ(setup.t2->getRoles()[0]->getStr(), 49);
}

TEST(ParserTest, CreatesEveryRequirementSkillByChineseName) {
    for (const std::string name : {"水球", "火球", "自我治療", "石化", "下毒", "召喚", "自爆", "鼓舞", "詛咒", "一拳攻擊"}) {
        SCOPED_TRACE(name);
        Skill* skill = RPG_parser::createSkill(name);
        ASSERT_NE(skill, nullptr);
        EXPECT_EQ(skill->getName(), name);
        delete skill;
    }
}

TEST(ParserTest, OnePunchGetsTheRequirementChain) {
    Troop t1(1), t2(2);
    Role* hero = new Role(1000, 1000, 0, "英雄");
    Role* slime = new Role(600, 0, 0, "Slime");
    t1.addRole(hero);
    t2.addRole(slime);

    Skill* punch = RPG_parser::createSkill("一拳攻擊");
    ASSERT_NE(dynamic_cast<OnePunch*>(punch), nullptr);
    std::ostringstream out;
    std::streambuf* old = std::cout.rdbuf(out.rdbuf());
    punch->attack(hero, {slime});
    std::cout.rdbuf(old);
    EXPECT_EQ(out.str(), "[1]英雄 對 [2]Slime 造成 300 點傷害。\n"); // 規則 1 生效：鏈已注入
    delete punch;
}

TEST(ParserTest, UnknownSkillIsRejected) {
    EXPECT_THROW(RPG_parser::createSkill("隕石"), std::invalid_argument);
    std::istringstream input("#軍隊-1-開始\n英雄 1 1 1 隕石\n#軍隊-1-結束\n#軍隊-2-開始\nS 1 0 0\n#軍隊-2-結束\n");
    EXPECT_THROW(RPG_parser::parse(input), std::invalid_argument);
}

TEST(ParserTest, MalformedInputIsRejected) {
    const std::vector<std::string> bad = {
        "",                                                                          // 空的
        "英雄 1 1 1\n",                                                              // 缺少開始標記
        "#軍隊-1-開始\n英雄 1 1 1\n",                                                // 缺少結束標記
        "#軍隊-1-開始\n英雄 1 1 1\n#軍隊-1-結束\n",                                  // 缺少軍隊 2
        "#軍隊-1-開始\n英雄 1 1 1\n#軍隊-1-結束\n#軍隊-2-開始\nS 1 0 0\n",           // 軍隊 2 沒有結束
        "#軍隊-1-開始\n英雄 abc 1 1\n#軍隊-1-結束\n#軍隊-2-開始\nS 1 0 0\n#軍隊-2-結束\n", // HP 不是數字
        "#軍隊-1-開始\n英雄 1 1\n#軍隊-1-結束\n#軍隊-2-開始\nS 1 0 0\n#軍隊-2-結束\n",     // 欄位不足
        "#軍隊-1-開始\n#軍隊-1-結束\n#軍隊-2-開始\nS 1 0 0\n#軍隊-2-結束\n",            // 軍隊 1 沒有英雄
    };
    for (const std::string& text : bad) {
        SCOPED_TRACE(text);
        std::istringstream input(text);
        EXPECT_THROW(RPG_parser::parse(input), std::invalid_argument);
    }
}

} // namespace

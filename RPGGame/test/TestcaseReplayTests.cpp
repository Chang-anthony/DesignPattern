/*
 * 整場輸入 → 輸出比對（D35–D39）：用正式的 RPG_parser + HeroAction + RPG 跑 testcases/ 的每一組 .in，
 * 輸出與 .out 逐行比對。
 *  - 每組一個參數化案例（TEST_P）；第一個不同的行會報出行號
 *  - 不一致時把實際輸出寫到「目前目錄/<名稱>.actual.txt」，方便用 diff 對照（D39）
 */
#include <gtest/gtest.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "RPG.hpp"
#include "Troop.hpp"
#include "Role.hpp"
#include "HeroAction.hpp"
#include "RPG_parser.hpp"

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

const std::filesystem::path kTestcaseDir = std::filesystem::path(__FILE__).parent_path().parent_path() / "testcases";

// 讀 .out：去掉行尾 '\r'（測資檔是 Windows 換行）與檔尾空行
Lines readExpected(const std::filesystem::path& path) {
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

// 與 main.cpp「RPGGAME <測資.in>」相同的流程：軍隊與英雄決策都來自同一個檔案
Lines playTestcase(const std::filesystem::path& inPath) {
    std::ifstream in(inPath);
    RPGSetup setup = RPG_parser::parse(in);
    setup.hero->setDecider(new HeroAction(in)); // Role 擁有決策者（D49）

    Lines lines;
    {
        CoutCapture capture;
        RPG rpg;
        rpg.GameStart(setup.t1, setup.t2);
        rpg.GameEnd();
        lines = capture.lines();
    }
    delete setup.t1; // Client 擁有兩軍（D49）
    delete setup.t2;
    return lines;
}

class TestcaseReplayTest : public ::testing::TestWithParam<std::string> {};

TEST_P(TestcaseReplayTest, OutputMatchesExpectedFile) {
    const std::string name = GetParam();
    const std::filesystem::path inPath = kTestcaseDir / (name + ".in");
    const std::filesystem::path outPath = kTestcaseDir / (name + ".out");
    ASSERT_TRUE(std::filesystem::exists(inPath)) << "找不到 " << inPath.string();
    ASSERT_TRUE(std::filesystem::exists(outPath)) << "找不到 " << outPath.string();

    Lines expected = readExpected(outPath);
    Lines actual = playTestcase(inPath);

    if (actual != expected) {
        std::ofstream dump(name + ".actual.txt");
        for (const std::string& line : actual) dump << line << "\n";
    }
    size_t n = std::min(actual.size(), expected.size());
    for (size_t i = 0; i < n; i++) {
        ASSERT_EQ(actual[i], expected[i]) << name << ".out 第 " << (i + 1) << " 行不同（實際輸出已寫到 "
                                          << name << ".actual.txt）";
    }
    EXPECT_EQ(actual.size(), expected.size()) << "行數不同（實際輸出已寫到 " << name << ".actual.txt）";
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

// 確認上面列出的就是 testcases/ 裡全部的 .in（新增測資時忘了加會在這裡失敗）
TEST(TestcaseListTest, EveryInputFileIsReplayed) {
    std::vector<std::string> names;
    for (const auto& entry : std::filesystem::directory_iterator(kTestcaseDir)) {
        if (entry.path().extension() == ".in") names.push_back(entry.path().stem().string());
    }
    std::sort(names.begin(), names.end());
    EXPECT_EQ(names, (std::vector<std::string>{"cheerup", "curse", "one-punch", "only-basic-attack", "petrochemical",
                                               "poison", "self-explosion", "self-healing", "summon",
                                               "waterball-and-fireball-1v2"}));
}

} // namespace

/*
 * io::Output（utils/Output.hpp）的單元測試。
 *  - 依據：CLAUDE.md 決策 D50（輸出用 Composite：Leaf 決定輸出到哪、Composite 決定渲染；單一存取點）
 */
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Output.hpp"
#include "Role.hpp"
#include "Troop.hpp"
#include "State.hpp"

namespace {

// 測試用的 Composite：每行前面加上 tag（示範「Composite 決定渲染」）
class PrefixOutput : public io::CompositeOutput {
public:
    PrefixOutput(std::string tag, std::vector<io::Output*> children)
        : io::CompositeOutput(std::move(children)), tag(std::move(tag)) {}

protected:
    std::string render(const std::string& line) override { return tag + line; }

private:
    std::string tag;
};

// 解構時計數 +1，確認 Composite 釋放子節點
class TrackedOutput : public io::Output {
public:
    explicit TrackedOutput(int* destroyed) : destroyed(destroyed) {}
    ~TrackedOutput() override { (*destroyed)++; }
    void write(const std::string&) override {}

private:
    int* destroyed;
};

// 每個測試結束都把單一存取點還原成預設，避免影響其他測試
class OutputTest : public ::testing::Test {
protected:
    void TearDown() override { io::setOutput(nullptr); }
};

// =====================================================================
// Leaf：決定輸出到哪
// =====================================================================

TEST_F(OutputTest, ConsoleOutputWritesLineToCout) {
    std::ostringstream captured;
    std::streambuf* old = std::cout.rdbuf(captured.rdbuf()); // 只有測 ConsoleOutput 本身才需要碰 std::cout
    io::ConsoleOutput console;
    console.write("輪到 [1]英雄");
    std::cout.rdbuf(old);
    EXPECT_EQ(captured.str(), "輪到 [1]英雄\n");
}

TEST_F(OutputTest, StreamOutputWritesLineToGivenStream) {
    std::ostringstream stream;
    io::StreamOutput output(stream);
    output.write("a");
    output.write("b");
    EXPECT_EQ(stream.str(), "a\nb\n");
}

// =====================================================================
// Composite：決定渲染，再分送
// =====================================================================

TEST_F(OutputTest, CompositeForwardsSameLineToAllChildrenInOrder) {
    std::ostringstream first, second;
    io::CompositeOutput output({new io::StreamOutput(first), new io::StreamOutput(second)});
    output.write("[2]Slime1 死亡。");
    EXPECT_EQ(first.str(), "[2]Slime1 死亡。\n");
    EXPECT_EQ(second.str(), "[2]Slime1 死亡。\n");
}

TEST_F(OutputTest, NestedCompositesRenderEachBranchIndependently) {
    // 主控台分支原樣、紀錄檔分支加前綴：渲染只影響自己底下的子節點
    std::ostringstream plain, logged;
    io::CompositeOutput output({
        new io::StreamOutput(plain),
        new PrefixOutput("[log] ", {new io::StreamOutput(logged)}),
    });
    output.write("你獲勝了！");
    EXPECT_EQ(plain.str(), "你獲勝了！\n");
    EXPECT_EQ(logged.str(), "[log] 你獲勝了！\n");
}

TEST_F(OutputTest, CompositeReleasesItsChildren) {
    int destroyed = 0;
    {
        io::CompositeOutput output({new TrackedOutput(&destroyed), new TrackedOutput(&destroyed)});
        EXPECT_EQ(destroyed, 0);
    }
    EXPECT_EQ(destroyed, 2);
}

// =====================================================================
// 單一存取點
// =====================================================================

TEST_F(OutputTest, DefaultIsConsoleAndSetOutputReturnsPreviousForRestore) {
    EXPECT_NE(dynamic_cast<io::ConsoleOutput*>(&io::output()), nullptr); // 未設定：主控台

    std::ostringstream a, b;
    io::StreamOutput outA(a), outB(b);
    EXPECT_EQ(io::setOutput(&outA), nullptr);   // 先前是預設
    EXPECT_EQ(io::setOutput(&outB), &outA);     // 回傳先前設定的，方便還原
    io::output().write("x");
    EXPECT_EQ(io::setOutput(&outA), &outB);     // 還原
    io::output().write("y");
    EXPECT_EQ(a.str(), "y\n");
    EXPECT_EQ(b.str(), "x\n");

    io::setOutput(nullptr);                      // nullptr：回到預設的主控台
    EXPECT_NE(dynamic_cast<io::ConsoleOutput*>(&io::output()), nullptr);
}

TEST_F(OutputTest, ModuleWritesOnlyThroughCurrentOutput) {
    // 模組（這裡是 Role 的死亡訊息與 State 的傷害訊息）寫到 io::output()，完全不碰 std::cout
    Troop t1(1), t2(2);
    Role* attacker = new Role(100, 0, 0, "A");
    Role* target = new Role(10, 0, 0, "B");
    t1.addRole(attacker);
    t2.addRole(target);

    std::ostringstream captured, console;
    io::StreamOutput sink(captured);
    io::setOutput(&sink);
    std::streambuf* old = std::cout.rdbuf(console.rdbuf());
    attacker->getState()->doDamage(target, 10);
    std::cout.rdbuf(old);

    EXPECT_EQ(captured.str(), "[1]A 對 [2]B 造成 10 點傷害。\n[2]B 死亡。\n");
    EXPECT_EQ(console.str(), ""); // std::cout 沒有收到任何東西
}

} // namespace

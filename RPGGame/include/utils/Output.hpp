#pragma once
#ifndef _UTILS_OUTPUT_H_
#define _UTILS_OUTPUT_H_

/*
 * 輸出小工具（D50）：模組只認得 io::Output，輸出到哪裡由 Client 組裝。
 *  - 放在 utils 資料夾；命名空間用 io（utils.h 的 utils 是 class，不能再當命名空間）
 *  - Leaf 決定輸出到哪：ConsoleOutput（主控台）、StreamOutput（任意 std::ostream，例如檔案、測試用的字串）
 *  - Composite 決定加上什麼渲染：先 render 一行，再依序交給所有子節點；巢狀組合可讓不同分支有不同渲染
 *  - 單一存取點：模組用 io::output().write(...)；Client 用 io::setOutput(...) 更換（未設定時是主控台）
 *
 * 用法（Client）：
 *     io::CompositeOutput out({new io::ConsoleOutput(), new io::StreamOutput(logFile)});
 *     io::Output* previous = io::setOutput(&out);
 *     ...
 *     io::setOutput(previous);
 */

#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

namespace io {

// 一次寫一整行（不含換行）
class Output {
public:
    virtual ~Output() = default;
    virtual void write(const std::string& line) = 0;
};

// Leaf：主控台。每行 flush，--play 時提示會在讀鍵盤之前出現
class ConsoleOutput : public Output {
public:
    void write(const std::string& line) override { std::cout << line << std::endl; }
};

// Leaf：任意串流（不擁有串流，由呼叫端保證它活得比 StreamOutput 久）
class StreamOutput : public Output {
public:
    explicit StreamOutput(std::ostream& target) : stream(target) {}
    void write(const std::string& line) override { stream << line << '\n'; }

private:
    std::ostream& stream;
};

// Composite：先渲染，再依序分送給子節點。擁有子節點，解構時釋放（比照 D49）。
// 要加新的渲染就繼承並覆寫 render()；預設原樣輸出（遊戲輸出必須與 testcases/*.out 一字不差）
class CompositeOutput : public Output {
public:
    explicit CompositeOutput(std::vector<Output*> outputs) : children(std::move(outputs)) {}
    ~CompositeOutput() override {
        for (Output* child : children) {
            delete child;
        }
    }
    CompositeOutput(const CompositeOutput&) = delete;
    CompositeOutput& operator=(const CompositeOutput&) = delete;

    void write(const std::string& line) final {
        const std::string rendered = render(line);
        for (Output* child : children) {
            child->write(rendered);
        }
    }

protected:
    virtual std::string render(const std::string& line) { return line; }

private:
    std::vector<Output*> children;
};

namespace detail {
inline Output*& currentOutput() {
    static Output* current = nullptr; // nullptr = 使用預設的主控台
    return current;
}
inline Output& defaultOutput() {
    static ConsoleOutput console;
    return console;
}
} // namespace detail

// 模組取用目前的輸出
inline Output& output() {
    Output* current = detail::currentOutput();
    return current ? *current : detail::defaultOutput();
}

// Client 更換輸出（不擁有，呼叫端負責釋放）；傳 nullptr 回到預設的主控台。回傳先前設定的值，方便還原
inline Output* setOutput(Output* next) {
    Output* previous = detail::currentOutput();
    detail::currentOutput() = next;
    return previous;
}

} // namespace io

#endif /* _UTILS_OUTPUT_H_ */

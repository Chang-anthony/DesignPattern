#include "HeroAction.hpp"
#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include "Role.hpp"

HeroAction::HeroAction(std::istream& input) : input(input) {}

std::vector<int> HeroAction::readDecision() {
    std::string line;
    while (std::getline(input, line)) {
        std::vector<int> numbers;
        std::stringstream ss(line);   // "0, 1, 2"：用 ',' 切開，前後空白與 Windows 的 '\r' 由 >> 略過
        std::string token;
        while (std::getline(ss, token, ',')) {
            std::stringstream ts(token);
            int value;
            if (ts >> value) numbers.push_back(value);
        }
        if (!numbers.empty()) return numbers; // 空白行略過
    }
    throw std::runtime_error("HeroAction: no more hero decisions in input");
}

Skill* HeroAction::chooseAction(const std::vector<Skill*>& skills) {
    std::vector<int> decision = readDecision();
    return skills.at(decision.front()); // 測資保證範圍合法；超出時 at() 丟 std::out_of_range
}

std::vector<Role*> HeroAction::chooseTargets(const std::vector<Role*>& candidates, int m) {
    int n = static_cast<int>(candidates.size());
    if (m <= 0 || n <= m) {
        return candidates; // 略過 S2：不讀輸入
    }
    // S2 的提示只在英雄真的要選時印（需求：「如果此為英雄的回合」；§7.2 I7）
    std::cout << "選擇 " << m << " 位目標:";
    for (int i = 0; i < n; i++) {
        std::cout << " (" << i << ") " << candidates[i]->getDisplayName();
    }
    std::cout << std::endl;

    std::vector<int> decision = readDecision();
    if (static_cast<int>(decision.size()) != m) {
        throw std::invalid_argument("HeroAction: expected " + std::to_string(m) + " target indices");
    }
    std::vector<Role*> targets;
    for (int index : decision) {
        targets.push_back(candidates.at(index));
    }
    return targets;
}

#include "RPG_parser.hpp"

#include <sstream>
#include <stdexcept>
#include <vector>

#include "Troop.hpp"
#include "Role.hpp"
#include "AIAction.hpp"
#include "Skill.hpp"
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
#include "HpHandler.hpp"
#include "PoisonPetrochemicalHandler.hpp"
#include "CheerupHandler.hpp"
#include "NormalHandler.hpp"

namespace {

// 讀下一個非空白行（去掉 Windows 的 '\r'）；讀不到回傳 false
bool nextLine(std::istream& input, std::string& line) {
    while (std::getline(input, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.find_first_not_of(" \t") != std::string::npos) {
            return true;
        }
    }
    return false;
}

void expect(std::istream& input, const std::string& marker) {
    std::string line;
    if (!nextLine(input, line) || line != marker) {
        throw std::invalid_argument("RPG_parser: expected \"" + marker + "\"");
    }
}

// 讀到 endMarker 為止，每行建立一位角色並加入 troop
void parseTroop(std::istream& input, Troop* troop, const std::string& endMarker) {
    std::string line;
    while (nextLine(input, line)) {
        if (line == endMarker) {
            return;
        }
        std::istringstream ss(line);
        std::string name;
        int hp = 0, mp = 0, str = 0;
        if (!(ss >> name >> hp >> mp >> str)) {
            throw std::invalid_argument("RPG_parser: bad role line \"" + line + "\"");
        }
        Role* role = new Role(hp, mp, str, name);
        std::string skillName;
        while (ss >> skillName) {
            role->addSkill(RPG_parser::createSkill(skillName));
        }
        troop->addRole(role);
    }
    throw std::invalid_argument("RPG_parser: missing \"" + endMarker + "\"");
}

} // namespace

RPGSetup RPG_parser::parse(std::istream& input) {
    RPGSetup setup{new Troop(1), new Troop(2), nullptr};

    expect(input, "#軍隊-1-開始");
    parseTroop(input, setup.t1, "#軍隊-1-結束");
    expect(input, "#軍隊-2-開始");
    parseTroop(input, setup.t2, "#軍隊-2-結束");

    if (setup.t1->getRoles().empty()) {
        throw std::invalid_argument("RPG_parser: troop 1 has no role (the hero is its first role)");
    }
    setup.hero = setup.t1->getRoles().front();
    setup.hero->setIdentity('h');

    for (Troop* troop : {setup.t1, setup.t2}) {
        for (Role* role : troop->getRoles()) {
            if (role != setup.hero) {
                role->setDecider(new AIAction());
            }
        }
    }
    return setup;
}

Skill* RPG_parser::createSkill(const std::string& name) {
    if (name == "水球") return new Waterball();
    if (name == "火球") return new Fireball();
    if (name == "自我治療") return new SelfHealing();
    if (name == "石化") return new Petrochemical();
    if (name == "下毒") return new Poison();
    if (name == "召喚") return new Summon();
    if (name == "自爆") return new SelfExplosion();
    if (name == "鼓舞") return new Cheerup();
    if (name == "詛咒") return new Curse();
    if (name == "一拳攻擊") {
        // 由上而下比對（需求「一拳攻擊」）；順序由 Client 決定（D21）
        return new OnePunch({new HpHandler(), new PoisonPetrochemicalHandler(), new CheerupHandler(), new NormalHandler()});
    }
    throw std::invalid_argument("RPG_parser: unknown skill \"" + name + "\"");
}

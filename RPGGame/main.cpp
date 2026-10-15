/*
* @author - (Anthony)
*
* RPG 主程式（Client）：解析輸入 → 建立兩軍 → 指定英雄的決策來源 → RPG 進行戰鬥。
*
* 用法：
*   RPGGAME <測資.in>            讀測資：軍隊與英雄決策都來自檔案（輸出可與 <測資.out> 比對）
*   RPGGAME --play <測資.in>     實際玩：軍隊來自檔案，英雄的每個決策由鍵盤輸入
*   RPGGAME                      軍隊與英雄決策都從標準輸入讀（可用 RPGGAME < 測資.in）
*   RPGGAME --help               顯示用法
*/
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "RPG.hpp"
#include "Troop.hpp"
#include "Role.hpp"
#include "HeroAction.hpp"
#include "RPG_parser.hpp"
#include "Output.hpp"

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

namespace {

void printUsage(const std::string& program) {
    std::cerr << "用法：\n"
              << "  " << program << " <測資.in>          讀測資：軍隊與英雄決策都來自檔案\n"
              << "  " << program << " --play <測資.in>   實際玩：軍隊來自檔案，英雄決策由鍵盤輸入\n"
              << "  " << program << "                    軍隊與英雄決策都從標準輸入讀\n";
}

// troopInput：軍隊定義的來源；heroInput：英雄決策的來源（D37）。兩者可以是同一個串流。
int play(std::istream& troopInput, std::istream& heroInput) {
    RPGSetup setup = RPG_parser::parse(troopInput);
    setup.hero->setDecider(new HeroAction(heroInput)); // 決策者交給英雄，由 Role 釋放（D49）

    // 輸出組裝（D50）：模組只寫 io::output()，輸出到哪由這裡決定。目前只有主控台；
    // 例如要同時寫戰鬥紀錄檔，再加一個 new io::StreamOutput(檔案) 即可
    io::CompositeOutput output({new io::ConsoleOutput()});
    io::Output* previous = io::setOutput(&output);

    RPG rpg;
    try {
        rpg.GameStart(setup.t1, setup.t2);
    } catch (...) {
        rpg.GameEnd();
        io::setOutput(previous);
        delete setup.t1; // Client 擁有兩軍；角色由 Troop 一併釋放（D49）
        delete setup.t2;
        throw;
    }
    rpg.GameEnd();
    io::setOutput(previous);
    delete setup.t1;
    delete setup.t2;
    return 0;
}

int playFile(const std::string& path, bool heroFromKeyboard) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "錯誤：無法開啟檔案 " << path << std::endl;
        return 1;
    }
    return heroFromKeyboard ? play(file, std::cin) : play(file, file);
}

} // namespace

int main(int argc, char** argv)
{
#ifdef _WIN32
    // 原始碼是 UTF-8，將 console 輸出 / 輸入改為 UTF-8 才能正確顯示與讀取中文
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    const std::string program = argc > 0 ? argv[0] : "RPGGAME";
    std::vector<std::string> args(argv + 1, argv + argc);

    try {
        if (args.empty()) {
            return play(std::cin, std::cin);
        }
        if (args[0] == "-h" || args[0] == "--help") {
            printUsage(program);
            return 0;
        }
        if (args.size() == 1) {
            return playFile(args[0], false);
        }
        if (args.size() == 2 && args[0] == "--play") {
            return playFile(args[1], true);
        }
        printUsage(program);
        return 1;
    } catch (const std::exception& e) {
        // 例如：輸入格式錯誤、未知技能、英雄的決策輸入用完
        std::cerr << "錯誤：" << e.what() << std::endl;
        return 1;
    }
}

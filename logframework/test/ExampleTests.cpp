#include <iostream>
#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <vector>
#include <fstream>
#include <Logger.hpp>
#include <Level.hpp>
#include <string>
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

std::vector<std::string> ReadFile(std::string path);

std::vector<std::string> ReadFile(std::string path)
{
    std::vector<std::string> lines;
    std::ifstream file(path);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }

    for (auto str: lines) {
        std::cout << str << std::endl;
    }

    return lines;
}


TEST(LevelTEST, Level) {
    Level level = Level::DEBUG;
    ASSERT_EQ(levelToString[level], "DEBUG");
}

int main(int argc, char **argv) {
#ifdef _WIN32
    // 原始碼是 UTF-8，將 console 輸出改為 UTF-8 才能正確顯示中文
    SetConsoleOutputCP(CP_UTF8);
#endif
    testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}


#include <iostream>
#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <vector>
#include <fstream>
#include <Logger.hpp>
#include <Level.hpp>
#include <string>

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
    testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}


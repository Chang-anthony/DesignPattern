#include <iostream>
#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <RelationshipAnalyer.hpp>
#include <RelationshipGraph.hpp>
#include <Friends.hpp>
#include <Relation.hpp>
#include <vector>
#include <fstream>

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

TEST(RelationshipGraph, RelationGraph) 
{
    std::string path = "C:\\Users\\JCCanthony\\Desktop\\DesignPatternCode\\friendship\\test\\text.txt";
    std::vector<std::string> lines = ReadFile(path);

    
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}


/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
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

int main()
{

    std::string path = "C:\\Users\\JCCanthony\\Desktop\\DesignPatternCode\\friendship\\script.txt";
    std::vector<std::string> lines = ReadFile(path);

    std::cout << "按下 Enter鍵 已結束遊戲" << std::endl;
    std::system("pause");
    return 0;
}
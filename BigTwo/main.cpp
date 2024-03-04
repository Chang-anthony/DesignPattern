/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "Player.hpp"
#include <utils.h>
#include <fstream>


static inline void readFile(std::string path) {
    std::ifstream inputFile(path);
    
    if(inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::cout << line << std::endl;
        }
        inputFile.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
}


//TODO: need to wirte simple test to test Round function
int main()
{
    readFile("C:/Users/JCCanthony/Desktop/DesignPatternCode/BigTwo/test/testSet/always-play-first-card.in");

    std::cout << "Test Input Multiple Numbers" << std::endl;
    std::vector<int> inputs = utils::InputMultipleNums();

    for(auto num : inputs){
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    std::cout << "按下 Enter 鍵已結束遊戲" << std::endl;
    std::system("pause");
    return 0;
}
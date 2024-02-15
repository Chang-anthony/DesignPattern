/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "Player.hpp"
#include <utils.h>



//TODO: need to wirte simple test to test Round function
int main()
{
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